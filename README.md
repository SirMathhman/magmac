# Magmac

This repository starts with basic boilerplate for a Python package.

## Setup

Create a virtual environment and install in editable mode:

```bash
python3 -m venv .venv
source .venv/bin/activate
pip install -e .
```

## Usage

Run the CLI entry point:

```bash
python -m magmac
```

## Running Tests

Install test requirements and run `pytest`:

```bash
pip install -r requirements-dev.txt
pytest
```


## Continuous Integration

This project uses GitHub Actions to run the test suite on pushes and pull requests.
