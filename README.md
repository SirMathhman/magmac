# magmac

This project contains a small translator written in C. It converts a very
simple function syntax. Functions can optionally specify an explicit return
type after the parameter list.

```
fn name() => {}
```

An explicit return type can be provided after the parameter list:

```
fn test(): I16 => {}
```

into an equivalent empty C function:

```
void name() {}
```

## Building

Compile the translator with GCC:

```
gcc -std=c11 -Wall -Wextra -o magmac magmac.c
```

## Usage

Run the program with an input file and optional output file name:

```
./magmac input.mc output.c
```

If no output file is provided, `out.c` is used by default.
