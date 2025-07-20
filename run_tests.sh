#!/bin/sh
set -e

for test_script in ./tests/test_*.sh; do
    echo "Running $test_script"
    sh "$test_script"
    echo
done

echo "All tests passed."
