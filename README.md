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

To create an output file based on an existing input file:

```bash
python -m magmac -i path/to/input.mg -o path/to/output.c
```

Currently the compiler supports a minimal syntax. A function declaration
`fn name() => {}` is translated into an empty C function:

```magma
fn empty() => {}
```

produces the following C code:

```c
void empty(void) {
}
```

Functions can also return booleans using `true` or `false` as the body. The
generated C uses `int` and returns `1` or `0`:

```magma
fn truthy() => true
fn falsy() => false
```

produces:

```c
int truthy(void) {
    return 1;
}

int falsy(void) {
    return 0;
}
```

Functions may also specify integer types. In Magma, types are written in
CamelCase, so integer types are `U8`, `U16`, `U32`, `U64`,
`I8`, `I16`, `I32`, and `I64`. Using one of these in the function body
generates a function returning the corresponding C integer type. Each function
returns `0` by default:

```magma
fn byte() => U8
fn word() => I32
```

produces:

```c
uint8_t byte(void) {
    return 0;
}

int32_t word(void) {
    return 0;
}
```

Functions may also take one or more parameters inside the parentheses. Each
parameter is written as `name : Type` and multiple parameters are separated by
commas:

```magma
fn id(x : I32) => I32

fn add(x : I32, y : I32) => I32
```

produces:

```c
int32_t id(int32_t x) {
    return 0;
}

int32_t add(int32_t x, int32_t y) {
    return 0;
}
```

## Running Tests

Install test requirements and run `pytest`:

```bash
pip install -r requirements-dev.txt
pytest
```


## Continuous Integration

This project uses GitHub Actions to run the test suite on pushes and pull requests.

## Coding Style

Magmac avoids nested loops entirely and keeps other nested structures to at most two levels of indentation so the code stays readable.
