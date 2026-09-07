# Makefile for the Akari API (wince-api)
#
# Copyright (c) 2026 Akari API contributors
# SPDX-License-Identifier: MIT

CC      ?= cc
CFLAGS  ?= -O2 -Wall -Wextra -Wshadow -Wstrict-prototypes
STD      = -std=c11
INCLUDES = -Iinclude

# CE deployment versions checked on the host (types/syntax only; the
# 32-bit pointer model is verified with the CE toolchain, see
# docs/verification.md).
CE_VERSIONS = 0x420 0x500 0x600

HDRS = include/windef.h include/winbase.h include/windows.h

.PHONY: check hostcheck defcheck clean

check: hostcheck defcheck

defcheck:
	@for f in def/coredll.def def/coredll4.def def/coredll6.def \
	  def/coredll6-x86.def; do \
	  [ -f $$f ] || { echo "missing $$f" >&2; exit 1; }; \
	  n=$$(awk '/^EXPORTS/{e=1;next} e && NF' $$f | wc -l); \
	  echo "[defcheck] $$f: $$n exports"; \
	  [ $$n -gt 1000 ] || { echo "def $$f looks empty" >&2; exit 1; }; \
	done

hostcheck: $(HDRS)
	@for v in $(CE_VERSIONS); do \
	  echo "[hostcheck] headers + TU under _WIN32_WCE=$$v"; \
	  cc $(STD) $(CFLAGS) -Werror -D_WIN32_WCE=$$v $(INCLUDES) -fsyntax-only \
	    tests/host/tu_compile.c || exit 1; \
	  for h in $(HDRS); do \
	    echo "  standalone: $$h"; \
	    cc $(STD) $(CFLAGS) -Werror -D_WIN32_WCE=$$v $(INCLUDES) \
	      -include $$h -fsyntax-only -x c /dev/null || exit 1; \
	  done; \
	done
	@echo "[hostcheck] OK -- headers compile warning-free for CE $(CE_VERSIONS)"

clean:
	rm -rf build
