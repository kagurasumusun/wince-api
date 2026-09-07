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

HDRS = include/windef.h include/winbase.h include/windows.h include/winerror.h

.PHONY: check hostcheck defcheck clean

check: hostcheck defcheck

# Import-library export defs (def/*.def) are OS-interface facts that
# ./gen-defs.sh regenerates out-of-tree from the device-dump-audited
# coredll export surface (audit-coredll.py in kagurasumusun/cellvm-build);
# they are intentionally not committed.  When present they are validated;
# when absent that is not an error.
defcheck:
	@found=0; for f in def/coredll.def def/coredll4.def def/coredll6.def \
	  def/coredll6-x86.def; do \
	  if [ -f "$$f" ]; then found=1; \
	    n=$$(awk '/^EXPORTS/{e=1;next} e && NF && $$0 !~ /^;/' "$$f" | wc -l); \
	    echo "[defcheck] $$f: $$n exports"; \
	    [ $$n -gt 1000 ] || { echo "def $$f looks empty" >&2; exit 1; }; \
	  fi; \
	done; \
	if [ $$found -eq 0 ]; then \
	  echo "[defcheck] no def/*.def present (regenerate with ./gen-defs.sh \
from the audited export surface when needed)"; \
	fi

# Cross checks with the real Windows CE LLVM/Clang toolchain
# (kagurasumusun/llvm-project, branch LLVM-WinCE).  The driver is
# selected with WINCECLANG, e.g.:
#   make crosscheck WINCECLANG=/path/to/wince-clang/bin/clang
# Compilation is freestanding against an empty sysroot so that only
# these headers (never host or CeGCC libc headers) are exercised.
WINCECLANG ?=
CE_TRIPLES = arm-pc-wince4.2 arm-pc-wince5.0 arm-pc-wince6.0 \
             i386-pc-wince4.2 i386-pc-wince5.0 i386-pc-wince6.0

crosscheck: $(HDRS)
	@if [ -z "$(WINCECLANG)" ]; then \
	  echo "[crosscheck] set WINCECLANG to the WinCE clang binary" >&2; \
	  exit 2; \
	fi; \
	tmp=$$(mktemp -d); trap 'rm -rf "$$tmp"' EXIT; \
	for t in $(CE_TRIPLES); do \
	  for h in $(HDRS); do \
	    echo "[crosscheck] $$t standalone: $$h"; \
	    "$(WINCECLANG)" -target $$t -std=c11 -ffreestanding \
	      --sysroot=$$tmp -Wno-wince-sysroot-missing \
	      $(CFLAGS) -Werror -I include -include $$h -fsyntax-only \
	      -x c /dev/null || exit 1; \
	  done; \
	  echo "[crosscheck] $$t TU"; \
	  "$(WINCECLANG)" -target $$t -std=c11 -ffreestanding \
	    --sysroot=$$tmp -Wno-wince-sysroot-missing \
	    $(CFLAGS) -Werror -I include -fsyntax-only \
	    tests/host/tu_compile.c || exit 1; \
	done; \
	echo "[crosscheck] OK -- $(words $(CE_TRIPLES)) WinCE targets"

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
