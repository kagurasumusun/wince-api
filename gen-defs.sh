#!/bin/sh
# Generate self-authored coredll export defs for wince-api.
#
# Extracts ONLY the export names/ordinals (OS interface facts dictated
# by coredll.dll itself) from the *device-dump-audited export surface*
# produced by the audit pipeline (audit-coredll.py in
# kagurasumusun/cellvm-build) and writes our own normalized def files.
#
# INPUT must be that audited surface -- never a stock third-party
# mingwrt/w32api def.  Point AUDIT_DIR at a directory holding the
# audited coredll{,4,6,-x86}.def files (pass it as the first argument
# or set AUDIT_DIR), e.g.:
#
#   AUDIT_DIR=/path/to/audited-export ./gen-defs.sh
#
# Output goes to def/ (not committed; see README).
set -e
AUDIT_DIR="${1:-${AUDIT_DIR:-}}"
if [ -z "$AUDIT_DIR" ] || [ ! -d "$AUDIT_DIR" ]; then
  echo "gen-defs.sh: AUDIT_DIR (audited export surface from the" >&2
  echo "  device-dump audit, audit-coredll.py) is required and must" >&2
  echo "  hold coredll{,4,6,-x86}.def.  Stock mingwrt/w32api defs are" >&2
  echo "  NOT an acceptable input." >&2
  exit 1
fi
mkdir -p def
for f in coredll coredll4 coredll6 coredll6-x86; do
  src="$AUDIT_DIR/$f.def"
  [ -f "$src" ] || { echo "gen-defs.sh: missing audited surface $src" >&2; exit 1; }
  out="def/$f.def"
  {
    echo "# $f.def -- COREDLL export surface for Windows CE (Akari API)."
    echo "#"
    echo "# Copyright (c) 2026 Akari API contributors"
    echo "# SPDX-License-Identifier: MIT"
    echo "#"
    echo "# Export names and ordinals are OS interface facts dictated by"
    echo "# coredll.dll itself; transcribed from the device-dump-audited export"
    echo "# surface of the verified toolchain sysroot (audit-coredll.py,"
    echo "# kagurasumusun/cellvm-build).  No third-party expression is included."
    echo "# No name is invented here: include/ headers declare only names present"
    echo "# in this surface (see docs/inventory.md)."
    echo "LIBRARY coredll.dll"
    echo "EXPORTS"
    awk '/^EXPORTS/{e=1;next} e && NF && $0 !~ /^[;#]/ {print}' "$src" | sort
  } > "$out"
  n=$(awk '/^EXPORTS/{e=1;next} e && NF' "$out" | wc -l)
  echo "$out: $n exports"
done
