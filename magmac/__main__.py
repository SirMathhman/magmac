"""CLI entry point for Magmac."""

import argparse


def main(argv=None):
    parser = argparse.ArgumentParser(description="Magmac CLI")
    parser.add_argument("--version", action="version", version="Magmac 0.1.0")
    args = parser.parse_args(argv)
    print("Hello from Magmac!")


if __name__ == "__main__":
    main()
