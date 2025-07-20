#!/bin/sh
set -e

gcc -std=c11 -Wall -Wextra -o magmac magmac.c

TMPDIR=$(mktemp -d)

echo 'fn is_true() => true' > "$TMPDIR/true.mc"
echo 'fn is_false() => false' > "$TMPDIR/false.mc"

./magmac "$TMPDIR/true.mc" "$TMPDIR/true.c"
./magmac "$TMPDIR/false.mc" "$TMPDIR/false.c"

grep -q 'int is_true() { return 1; }' "$TMPDIR/true.c"
grep -q 'int is_false() { return 0; }' "$TMPDIR/false.c"

echo "Boolean tests passed."
rm -r "$TMPDIR"
