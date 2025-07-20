# Magmac

Magmac is an experiment in building a self-hosted compiler. The goal is to
compile a custom language, **Magma**, to C. This repository currently starts
with basic Python package boilerplate and will evolve into the compiler
implementation.

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
