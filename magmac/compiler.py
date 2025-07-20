import re
from pathlib import Path


def compile_source(source: str) -> str:
    """Compile a Magma source string to C code."""
    pattern = re.compile(r"fn\s+(\w+)\s*\(\)\s*=>\s*{\s*}")
    output_lines = []
    for match in pattern.finditer(source):
        name = match.group(1)
        output_lines.append(f"void {name}(void) {{\n}}\n")
    return "".join(output_lines)


def compile_file(input_path: Path, output_path: Path) -> None:
    """Compile a file containing Magma code into a C file."""
    src = input_path.read_text()
    c_code = compile_source(src)
    output_path.write_text(c_code)
