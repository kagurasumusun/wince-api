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

HDRS = include/windef.h include/winbase.h include/windows.h include/winnls.h include/winreg.h include/psapi.h include/tlhelp32.h \
       include/msgqueue.h include/excpt.h include/dbgapi.h include/errorrep.h include/celog.h include/natedit.h \
       include/winuser.h include/winerror.h include/winnt.h include/wingdi.h include/tvout.h \
       include/notify.h include/shellapi.h include/commctrl.h \
       include/winsock2.h include/ws2tcpip.h include/ws2spi.h \
       include/tapi.h include/tapicomn.h \
       include/imm.h include/wincrypt.h include/winscard.h \
       include/objbase.h \
       include/aygshell.h include/shellsdk.h include/newmenu.h \
       include/shlobj.h include/shobjidl.h include/shtypes.h \
       include/extfile.h include/shelwapi.h include/cpl.h \
       include/sipapi.h include/sip.h \
       include/keybd.h include/pwinuser.h \
       include/windowsx.h include/commdlg.h \
       include/winldap.h include/winber.h \
       include/cchannel.h include/discodlg.h \
       include/prsht.h \
       include/bthsdpdef.h include/bt_api.h include/ws2bth.h include/bthapi.h \
       include/btagpub.h include/btagnetwork.h \
       include/snmp.h include/snmpapi.h include/snmpexts.h \
       include/pm.h include/ceddk.h \
       include/dvddrvr.h include/dvdcss.h \
       include/ddraw.h include/dvp.h \
       include/urlmon.h \
       include/mlang.h \
       include/mmsystem.h \
       include/imaging.h \
       include/pimstore.h

.PHONY: check hostcheck defcheck defdoc e2e clean

check: hostcheck defcheck

# defdoc regenerates def/*-doc.def from build/rows.json, the record set
# harvested from the official CE documentation pages by tools/ce-fetch.py
# (Requirement rows of the (v=msdn.10) archive).  tools/gen-doc-def.py
# only lists names that both (a) appear on a harvested page whose
# documented Link Library row names the DLL and (b) are declared as
# exports by these headers.  No shared-source, device-dump, VS or
# Platform Builder material is an input.
defdoc:
	@test -f build/rows.json || { echo "build/rows.json missing: run \
tools/ce-fetch.py on tools/manifests/core-*.manifest first" >&2; exit 1; }
	python3 tools/gen-doc-def.py

# defcheck validates the committed doc-derived defs (one per documented
# Link Library token, e.g. coredll-doc.def, coreloc-doc.def,
# toolhelp-doc.def, lmem-doc.def, loadstr-doc.def).
defcheck:
	@ok=1; found=0; \
	for f in def/*-doc.def; do \
	  [ -e "$$f" ] || continue; found=1; \
	  n=$$(awk '/^EXPORTS/{e=1;next} e && NF && $$0 !~ /^[;#]/' "$$f" | wc -l); \
	  echo "[defcheck] $$f: $$n exports"; \
	  [ $$n -gt 0 ] || { echo "def $$f looks empty" >&2; ok=0; }; \
	done; \
	if [ $$found -eq 0 ]; then \
	  echo "[defcheck] missing def/*-doc.def (run 'make defdoc')" >&2; \
	  exit 1; \
	fi; \
	[ $$ok -eq 1 ]

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

# End-to-end link checks: the doc-derived def files are turned into
# import libraries with llvm-dlltool (armce for ARM, i386
# --no-leading-underscore for x86 -- the CE coredll x86 export
# surface is undecorated, the headers are pinned to it, see
# windef.h), and the tests/e2e consumers are linked with lld-link
# -wince against the Akari CRT (wince-crt) startup objects into PE
# images (main app / WinMain app / DLL).  The images' machine type,
# CE subsystem and coredll import names are asserted with
# llvm-readobj.
#   make e2e WINCECLANG=/path/to/clang CRTDIR=/path/to/wince-crt
CRTDIR    ?= $(abspath $(CURDIR)/../wince-crt)

# M39 note: the M39 ws2 import assertions below resolve through ws2.dll (Ws2.lib
# per the official CE pages).
e2e:
	@if [ -z "$(WINCECLANG)" ]; then \
	  echo "[e2e] set WINCECLANG to the WinCE clang binary" >&2; \
	  exit 2; \
	fi; \
	if [ ! -f "$(CRTDIR)/src/crt/crt0.c" ]; then \
	  echo "[e2e] set CRTDIR to a wince-crt checkout (got $(CRTDIR))" >&2; \
	  exit 2; \
	fi; \
	bin=$$(dirname "$(WINCECLANG)"); \
	tmp=$$(mktemp -d); trap 'rm -rf "$$tmp"' EXIT; \
	for t in $(CE_TRIPLES); do \
	  case $$t in arm*) dtf="-m armce"; mchk="IMAGE_FILE_MACHINE_ARM";; \
	             *)    dtf="-m i386 --no-leading-underscore"; mchk="IMAGE_FILE_MACHINE_I386";; \
	  esac; \
	  d=build/e2e/$$t; mkdir -p $$d; \
	  for f in def/*-doc.def; do \
	    b=$$(basename $$f .def); \
	    "$$bin/llvm-dlltool" $$dtf -d $$f -l $$d/$$b.lib >/dev/null || exit 1; \
	  done; \
	  (cd "$(CRTDIR)" && make clean >/dev/null 2>&1 \
	     && make TARGET=$$t CC=$$bin/clang AR=$$bin/llvm-ar >/dev/null 2>&1) || { \
	    echo "[e2e] wince-crt build failed for $$t" >&2; exit 1; }; \
	  for s in e2e_console e2e_winmain e2e_module; do \
	    echo "[e2e] $$t compile: $$s"; \
	    "$(WINCECLANG)" -target $$t -std=c11 -ffreestanding \
	      --sysroot=$$tmp -Wno-wince-sysroot-missing \
	      $(CFLAGS) -Werror -I include -c tests/e2e/$$s.c -o $$d/$$s.o || exit 1; \
	  done; \
	  echo "[e2e] $$t link: main app / WinMain app / DLL"; \
	  "$$bin/lld-link" -wince /subsystem:windowsce /entry:mainACRTStartup \
	    /base:0x10000 /fixed $$d/e2e_console.o \
	    "$(CRTDIR)/build/akari_crt0.o" "$(CRTDIR)/build/libakari.a" \
	    $$d/*.lib /out:$$d/e2e_console.exe 2>/dev/null || exit 1; \
	  "$$bin/lld-link" -wince /subsystem:windowsce /entry:WinMainCRTStartup \
	    /base:0x10000 /fixed $$d/e2e_winmain.o \
	    "$(CRTDIR)/build/akari_crt0.o" "$(CRTDIR)/build/libakari.a" \
	    $$d/*.lib /out:$$d/e2e_winmain.exe 2>/dev/null || exit 1; \
	  "$$bin/lld-link" -wince /dll /entry:DllMainCRTStartup /base:0x10000 \
	    /export:E2EDemo $$d/e2e_module.o \
	    "$(CRTDIR)/build/akari_dllcrt.o" "$(CRTDIR)/build/libakari.a" \
	    $$d/*.lib /out:$$d/e2e_module.dll 2>/dev/null || exit 1; \
	  "$$bin/llvm-readobj" -h $$d/e2e_console.exe | grep -q "$$mchk" || exit 1; \
	  "$$bin/llvm-readobj" -h $$d/e2e_console.exe \
	    | grep -q "IMAGE_SUBSYSTEM_WINDOWS_CE_GUI" || exit 1; \
	  "$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	    | grep -q "Name: coredll.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CopyFileExW" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: ws2.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: WSAStartup" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: socket" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: getaddrinfo" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: WSAEnumNameSpaceProviders" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: WSALookupServiceBegin" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: WSASetService" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CommandBar_Create" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CommandBands_Create" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: GetOpenFileName" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: ldap_init" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: ber_alloc_t" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: WSPStartup" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: NSPSetService" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: TSPI_lineOpen" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: TSPI_phoneGetDevCaps" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: ole32.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CoCreateGuid" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CreateFileMoniker" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: StgCreateDocfile" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: oleaut32.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SysAllocString" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: VariantInit" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: LoadTypeLib" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: lineInitializeEx" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: lineOpen (" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: lineForward (" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: phoneOpen" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: TSPI_lineForward" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: coreimm.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: ImmGetContext" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: ImmSIPanelState" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CryptAcquireContext" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CryptMsgClose" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CryptProtectData" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: crypt32.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CertOpenStore" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CryptEncodeObjectEx" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: PFXImportCertStore" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: winscard.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SCardEstablishContext" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SCardTransmit" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: aygshell.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SHCreateMenuBar" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SHHandleWMActivate" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SHInitDialog" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SHGetAutoRunPath" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SipGetInfo" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SipShowIM" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SHSipPreference" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: kbdui.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: PostKeybdMessage" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: GetAsyncShiftFlags" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: KeybdGetDeviceInfo" || exit 1; \
	  "$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	    | grep -q "Name: ceshell.dll" || exit 1; \
	  "$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	    | grep -q "Symbol: SHBrowseForFolder" || exit 1; \
	  "$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	    | grep -q "Symbol: SHGetSpecialFolderLocation" || exit 1; \
	  "$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	    | grep -q "Symbol: StrRetToBuf" || exit 1; \
	  "$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	    | grep -q "Name: shmisc.dll" || exit 1; \
	  "$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	    | grep -q "Symbol: SHShowOutOfMemory" || exit 1; \
	  "$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	    | grep -q "Symbol: ShellExecuteEx" || exit 1; \
	  "$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	    | grep -q "Symbol: SHGetSpecialFolderPath" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: btdrt.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: BthReadLocalAddr" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: BthPerformInquiry" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: BthNsLookupServiceBegin" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: snmpapi.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SnmpUtilOidCmp" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SnmpUtilMemAlloc" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SnmpTfxOpen" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: snmp.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SnmpExtensionQuery" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: ceddk.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: HalAllocateCommonBuffer" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: READ_PORT_ULONG" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: MmMapIoSpace" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: btagsvc_phoneext.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: BthAGPhoneExtInit" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: btagsvc_network.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: BthAGNetworkDropCall" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: btagsvc.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: BthAGOnNetworkEvent" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: ddraw.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: DirectDrawCreate" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: DirectDrawCreateClipper" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: DirectDrawEnumerate" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: DirectDrawEnumerateEx" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: urlmon.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CoInternetGetSession" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CoInternetGetSecurityUrl" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CreateURLMoniker" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: RegisterMediaTypes" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: IsLoggingEnabledW" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: URLDownloadToFileW" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: WriteHitLogging" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: mlang.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: ConvertINetString" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: LcidToRfc1766" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: Rfc1766ToLcid" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_winmain.exe \
    | grep -q "Symbol: MessageBoxW" || exit 1; \
	  echo "[e2e] $$t OK (machine/subsystem/imports)"; \
	done; \
	echo "[e2e] OK -- $(words $(CE_TRIPLES)) WinCE targets linked against the doc-derived import libraries"
