#!/bin/sh
set -e

gcc -std=c11 -Wall -Wextra -o magmac magmac.c

TMPDIR=$(mktemp -d)

echo 'fn get_u8() => U8' > "$TMPDIR/u8.mc"
echo 'fn get_i64() => I64' > "$TMPDIR/i64.mc"

./magmac "$TMPDIR/u8.mc" "$TMPDIR/u8.c"
./magmac "$TMPDIR/i64.mc" "$TMPDIR/i64.c"

grep -q 'uint8_t get_u8() { return 0; }' "$TMPDIR/u8.c"
grep -q 'int64_t get_i64() { return 0; }' "$TMPDIR/i64.c"

echo "Integer tests passed."
rm -r "$TMPDIR"
