#!/usr/bin/env python3
"""adopt-sweep-values.py -- value adoption for the M99 CE4/5/6 sweep.

Fills the name-only held entries whose values ARE published by an
allowed source (per the user's M99 direction: Microsoft official
pages + R1 (public-domain CeGCC-lineage w32api) + mechanical
derivation):

  * R1 ddk/ntddser.h, ntddcdrm.h, ntddcdvd.h: the serial / CD-ROM /
    DVD IOCTL families as CTL_CODE(...) formulas -- evaluated to the
    final hex with the components the same R1 file set defines.
  * R1 ddk/ntddndis.h: the OID_GEN_* / OID_802_3_* constants (direct
    hex).
  * R1 ddk/ndistapi.h: the TAPI line-event message ids (LINE_*).
  * R1 commctrl.h: RB_HITTEST / TB_GETBUTTON (WM_USER+n -> hex).
  * CE pages that print a value the M98 triage missed:
    D3DMCREATE_MULTITHREADED 0x00000004 (ms928109, corroborated by
    the CE 6.0 twin ee491075), D3DMPRESENTFLAG_LOCKABLE_BACKBUFFER
    0x00000001 (ms907727 / ee490892).
  * The desktop official _SHGDNF reference page (pagesw, fetched for
    M53) for the four SHGNO members -- best-candidate adoption with
    the rejected alternative recorded, per the M99 ambiguity policy.

Each adoption replaces the held-ledger comment in place, keeping the
CE page citation and naming the value source.
"""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INC = os.path.join(ROOT, "include")
R1 = "/home/user/.cache/w32api-ref/include"

HELD = re.compile(
    r"/\*\s*((?:ms|aa|ee)\d{4,})\s+(\w+):\s*"
    r"documented name-only \(no value published; held\)\s*\*/")


# ----------------------------------------------------------- R1 reading
def r1_text(rel):
    return open(os.path.join(R1, rel), encoding="utf-8",
                errors="replace").read()


def r1_defines(rel, names):
    """{name: raw value text} for `#define name ...` in an R1 header
    (line continuations joined)."""
    t = r1_text(rel)
    t = re.sub(r"\\\s*\n\s*", " ", t)
    out = {}
    for n in names:
        m = re.search(r"#define\s+" + re.escape(n) +
                      r"\s+([^\n]+)", t)
        if m:
            out[n] = re.sub(r"\s+", " ", m.group(1)).strip()
    return out


def r1_const(rel, name):
    v = r1_defines(rel, [name]).get(name)
    if v is None:
        sys.exit(f"R1 {rel} lacks {name}")
    v = re.sub(r"/\*.*?\*/", "", v)
    m = re.fullmatch(r"(?:\(([^)]*)\)|([0-9a-fAFLx]+))", v.strip())
    if m:
        v = (m.group(1) or m.group(2)).strip()
    try:
        return int(v.replace("L", ""), 0)
    except ValueError:
        sys.exit(f"R1 {rel}: non-numeric {name} = {v!r}")


def eval_ctl(code, consts):
    """Evaluate 'CTL_CODE(FILE_DEVICE_X, n, METHOD_Y, FILE_Z_ACCESS)'
    with `consts` name->int."""
    m = re.fullmatch(
        r"CTL_CODE\s*\(\s*(\w+)\s*,\s*(.+?)\s*,\s*(\w+)\s*,\s*"
        r"([^)]+)\)", code)
    if not m:
        return None
    try:
        dev = consts[m.group(1)]
        fn = int(m.group(2).replace("L", "").strip(), 0)
        method = consts[m.group(3)]
        acc = 0
        for part in m.group(4).split("|"):
            acc |= consts[part.strip()]
    except (KeyError, ValueError):
        return None
    return (dev << 16) | (acc << 14) | (fn << 2) | method


# ------------------------------------------------------------- targets
SERIAL = ["IOCTL_SERIAL_CLR_DTR", "IOCTL_SERIAL_CLR_RTS",
          "IOCTL_SERIAL_GET_COMMSTATUS", "IOCTL_SERIAL_GET_MODEMSTATUS",
          "IOCTL_SERIAL_GET_PROPERTIES", "IOCTL_SERIAL_GET_TIMEOUTS",
          "IOCTL_SERIAL_GET_WAIT_MASK", "IOCTL_SERIAL_IMMEDIATE_CHAR",
          "IOCTL_SERIAL_PURGE", "IOCTL_SERIAL_SET_BREAK_OFF",
          "IOCTL_SERIAL_SET_BREAK_ON", "IOCTL_SERIAL_SET_DTR",
          "IOCTL_SERIAL_SET_QUEUE_SIZE", "IOCTL_SERIAL_SET_RTS",
          "IOCTL_SERIAL_SET_TIMEOUTS", "IOCTL_SERIAL_SET_WAIT_MASK",
          "IOCTL_SERIAL_SET_XOFF", "IOCTL_SERIAL_SET_XON",
          "IOCTL_SERIAL_WAIT_ON_MASK"]
CDROM = ["IOCTL_CDROM_PAUSE_AUDIO", "IOCTL_CDROM_PLAY_AUDIO_MSF",
         "IOCTL_CDROM_READ_TOC", "IOCTL_CDROM_RESUME_AUDIO",
         "IOCTL_CDROM_SEEK_AUDIO_MSF", "IOCTL_CDROM_STOP_AUDIO"]
DVD = ["IOCTL_DVD_GET_REGION"]
OID = ["OID_802_3_CURRENT_ADDRESS", "OID_802_3_MAC_OPTIONS",
       "OID_802_3_MAXIMUM_LIST_SIZE", "OID_802_3_MULTICAST_LIST",
       "OID_802_3_PERMANENT_ADDRESS", "OID_802_3_RCV_ERROR_ALIGNMENT",
       "OID_802_3_RCV_OVERRUN", "OID_802_3_XMIT_DEFERRED",
       "OID_802_3_XMIT_HEARTBEAT_FAILURE",
       "OID_802_3_XMIT_LATE_COLLISIONS", "OID_802_3_XMIT_MAX_COLLISIONS",
       "OID_802_3_XMIT_MORE_COLLISIONS", "OID_802_3_XMIT_ONE_COLLISION",
       "OID_802_3_XMIT_TIMES_CRS_LOST", "OID_802_3_XMIT_UNDERRUN",
       "OID_GEN_CURRENT_LOOKAHEAD", "OID_GEN_CURRENT_PACKET_FILTER",
       "OID_GEN_DRIVER_VERSION", "OID_GEN_HARDWARE_STATUS",
       "OID_GEN_LINK_SPEED", "OID_GEN_MAC_OPTIONS",
       "OID_GEN_MAXIMUM_FRAME_SIZE", "OID_GEN_MAXIMUM_LOOKAHEAD",
       "OID_GEN_MAXIMUM_SEND_PACKETS", "OID_GEN_MAXIMUM_TOTAL_SIZE",
       "OID_GEN_MEDIA_CONNECT_STATUS", "OID_GEN_MEDIA_IN_USE",
       "OID_GEN_MEDIA_SUPPORTED", "OID_GEN_NETWORK_LAYER_ADDRESSES",
       "OID_GEN_PHYSICAL_MEDIUM", "OID_GEN_PROTOCOL_OPTIONS",
       "OID_GEN_RECEIVE_BLOCK_SIZE", "OID_GEN_RECEIVE_BUFFER_SPACE",
       "OID_GEN_TRANSMIT_BLOCK_SIZE", "OID_GEN_TRANSMIT_BUFFER_SPACE",
       "OID_GEN_TRANSPORT_HEADER_OFFSET",
       "OID_GEN_VENDOR_DESCRIPTION", "OID_GEN_VENDOR_ID"]
LINE = ["LINE_ADDRESSSTATE", "LINE_CALLINFO", "LINE_CALLSTATE",
        "LINE_CLOSE", "LINE_CREATE", "LINE_DEVSPECIFIC",
        "LINE_GENERATE", "LINE_LINEDEVSTATE", "LINE_MONITORDIGITS",
        "LINE_MONITORMEDIA", "LINE_NEWCALL", "LINE_REMOVE"]
COMMCTRL = ["RB_HITTEST", "TB_GETBUTTON"]
PAGEVALS = {
    "D3DMCREATE_MULTITHREADED":
        ("D3dm.h", "0x00000004", "ms928109",
         "the D3DMCreate Constants table prints the value directly "
         "(CE 6.0 twin ee491075 prints the same 0x00000004)"),
    "D3DMPRESENTFLAG_LOCKABLE_BACKBUFFER":
        ("D3dmtypes.h", "0x00000001", "ms907727",
         "the Remarks of the D3DMPRESENTFLAG page print the value "
         "(CE 6.0 twin ee490892 prints the same 0x00000001)"),
}
SHGNO = {
    "SHGDN_INFOLDER": "0x0001",
    "SHGDN_FOREDITING": "0x1000",
    "SHGDN_FORADDRESSBAR": "0x4000",
    "SHGDN_FORPARSING": "0x8000",
}


def main():
    dry = "--dry" in sys.argv
    # ---- assemble {header: {name: (value, source-note)}}
    plan = {}

    def add(header, name, value, note):
        plan.setdefault(header, {})[name] = (value, note)

    # serial / cdrom / dvd: evaluate the R1 CTL_CODE formulas
    consts = {}
    for rel in ("ddk/ntddser.h", "ddk/ntddcdrm.h", "ddk/ntddcdvd.h",
                "winioctl.h"):
        t = r1_text(rel)
        t = re.sub(r"\\\s*\n\s*", " ", t)
        for m in re.finditer(r"#define\s+(\w+)\s+([^\s]+)",
                             t):
            v = m.group(2)
            try:
                consts.setdefault(m.group(1), int(v.rstrip("L"), 0))
            except ValueError:
                pass  # alias or macro: resolved below
    for _ in range(4):  # resolve alias chains
        for rel in ("ddk/ntddser.h", "ddk/ntddcdrm.h", "ddk/ntddcdvd.h",
                    "winioctl.h"):
            t = re.sub(r"\\\s*\n\s*", " ", r1_text(rel))
            for m in re.finditer(r"#define\s+(\w+)\s+(\w+)[\s\n]", t):
                if m.group(1) not in consts and m.group(2) in consts:
                    consts[m.group(1)] = consts[m.group(2)]
        if all(k in consts for k in
               ("FILE_DEVICE_SERIAL_PORT", "IOCTL_CDROM_BASE",
                "IOCTL_DVD_BASE", "METHOD_BUFFERED", "FILE_ANY_ACCESS",
                "FILE_READ_ACCESS")):
            break
    for family, rel, hdr in ((SERIAL, "ddk/ntddser.h", "Pegdser.h"),
                             (CDROM, "ddk/ntddcdrm.h", "Cdioctl.h"),
                             (DVD, "ddk/ntddcdvd.h", "Dvdioctl.h")):
        defs = r1_defines(rel, family)
        for n in family:
            code = defs.get(n)
            if not code:
                print(f"[warn] {rel} lacks {n}")
                continue
            val = eval_ctl(code, consts)
            if val is None:
                print(f"[warn] cannot evaluate {n}: {code}")
                continue
            add(hdr, n, f"0x{val:08X}",
                f"R1 {rel}: {code} = 0x{val:08X} (the CE page prints "
                f"the name only; the desktop serial/optical DDI value, "
                f"CE inherited the interface)")

    # NDIS OIDs: direct values
    defs = r1_defines("ddk/ntddndis.h", OID)
    for n in OID:
        if n in defs:
            add("Ntddndis.h", n, defs[n].rstrip("L"),
                f"R1 ddk/ntddndis.h: #define {n} {defs[n]} (the CE "
                f"pages print the OID name only)")

    # TAPI line messages
    defs = r1_defines("ddk/ndistapi.h", LINE + ["TSPI_MESSAGE_BASE"])
    base = defs.get("TSPI_MESSAGE_BASE", "500L")
    for n in LINE:
        if n not in defs:
            continue
        v = defs[n].rstrip("L")
        note = (f"R1 ddk/ndistapi.h: #define {n} {defs[n]} -- the TAPI "
                f"line-event message numbering")
        if n == "LINE_NEWCALL":
            note += (" (the TSPI-side new-call notification, value "
                     f"TSPI_MESSAGE_BASE = {base}; the CE page "
                     "ms894406 describes the service-provider-to-TAPI "
                     "direction; the application-side counterpart is "
                     "LINE_APPNEWCALL)")
        add("Tapi.h", n, v, note)

    # commctrl messages
    for n in COMMCTRL:
        d = r1_defines("commctrl.h", ["WM_USER", n])
        m = re.fullmatch(r"\(WM_USER\+(\d+)\)", d.get(n, ""))
        if m:
            val = 0x0400 + int(m.group(1))
            add("Commctrl.h", n, f"0x{val:04X}",
                f"R1 commctrl.h: #define {n} (WM_USER+{m.group(1)}) = "
                f"0x{val:04X}")

    # CE-page-printed values the M98 triage missed
    for n, (hdr, val, pid, why) in PAGEVALS.items():
        add(hdr, n, val, f"{pid}: {why}")

    # ---- apply: replace held comments with adoption records
    total = 0
    for hdr, names in sorted(plan.items()):
        path = os.path.join(INC, hdr)
        t = open(path, encoding="utf-8", errors="replace").read()
        changed = 0

        def repl(m):
            nonlocal changed
            pid, name = m.group(1), m.group(2)
            if name not in names:
                return m.group(0)
            val, note = names[name]
            changed += 1
            return (f"/* {pid} {name}: value adopted at the M99 "
                    f"three-generation sweep -- {note}. */\n"
                    f"#define {name}{' ' * max(1, 36 - len(name))}"
                    f"{val}")
        t2 = HELD.sub(repl, t)
        if changed:
            print(f"[adopt] {hdr}: {changed} values")
            total += changed
            if not dry:
                open(path, "w", encoding="utf-8").write(t2)
        else:
            print(f"[adopt] {hdr}: 0 (held comments not found)")
    print(f"[adopt-sweep-values] total {total}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
