"""CLI entry point for Magmac."""

import argparse
from pathlib import Path

from .compiler import compile_file


def main(argv=None):
    parser = argparse.ArgumentParser(description="Magmac CLI")
    parser.add_argument("--version", action="version", version="Magmac 0.1.0")
    parser.add_argument("-i", "--input", help="Input file")
    parser.add_argument("-o", "--output", help="Output file")
    args = parser.parse_args(argv)

    print("Hello from Magmac!")

    if args.input and args.output:
        in_path = Path(args.input)
        out_path = Path(args.output)
        if in_path.exists():
            compile_file(in_path, out_path)
            print(f"Created {args.output}")


if __name__ == "__main__":
    main()
