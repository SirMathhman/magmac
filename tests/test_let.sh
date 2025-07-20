#!/bin/sh
set -e

gcc -std=c11 -Wall -Wextra -o magmac magmac.c

TMPDIR=$(mktemp -d)

echo 'let count: U32 = 5;' > "$TMPDIR/let.mc"

./magmac "$TMPDIR/let.mc" "$TMPDIR/let.c"

grep -q 'uint32_t count = 5;' "$TMPDIR/let.c"

echo "Let statement test passed."
rm -r "$TMPDIR"
