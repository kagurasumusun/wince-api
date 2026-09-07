#!/bin/sh
# Generate self-authored coredll export defs for wince-api.
# Extracts ONLY the export names/ordinals (OS interface facts) from
# the device-dump-audited toolchain surface; writes our own files.
set -e
mkdir -p def
for f in coredll coredll4 coredll6 coredll6-x86; do
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
    awk '/^EXPORTS/{e=1;next} e && NF && $0 !~ /^;/ {print}' "/tmp/mingwrt/$f.def" | sort
  } > "$out"
  n=$(awk '/^EXPORTS/{e=1;next} e && NF' "$out" | wc -l)
  echo "$out: $n exports"
done
