#!/bin/sh
set -e

gcc -std=c11 -Wall -Wextra -o magmac magmac.c

TMPDIR=$(mktemp -d)

echo 'fn foo(): I16 => {}' > "$TMPDIR/explicit.mc"

./magmac "$TMPDIR/explicit.mc" "$TMPDIR/explicit.c"

grep -q 'int16_t foo() {}' "$TMPDIR/explicit.c"

echo "Explicit return type test passed."
rm -r "$TMPDIR"
