import os
import sys

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))

from magmac.__main__ import main


def test_main_output(capsys):
    main([])
    captured = capsys.readouterr()
    assert "Hello from Magmac!" in captured.out


def test_compile_empty_function(tmp_path):
    input_file = tmp_path / "in.mg"
    input_file.write_text("fn empty() => {}")
    output_file = tmp_path / "out.c"
    main(["-i", str(input_file), "-o", str(output_file)])
    assert output_file.read_text() == "void empty(void) {\n}\n"


def test_compile_boolean_functions(tmp_path):
    src = "\n".join([
        "fn truthy() => true",
        "fn falsy() => false",
    ])
    input_file = tmp_path / "in.mg"
    input_file.write_text(src)
    output_file = tmp_path / "out.c"
    main(["-i", str(input_file), "-o", str(output_file)])
    expected = (
        "int truthy(void) {\n    return 1;\n}\n"
        "int falsy(void) {\n    return 0;\n}\n"
    )
    assert output_file.read_text() == expected


def test_compile_integer_functions(tmp_path):
    src = "\n".join([
        "fn byte() => U8",
        "fn word() => I32",
    ])
    input_file = tmp_path / "in.mg"
    input_file.write_text(src)
    output_file = tmp_path / "out.c"
    main(["-i", str(input_file), "-o", str(output_file)])
    expected = (
        "uint8_t byte(void) {\n    return 0;\n}\n"
        "int32_t word(void) {\n    return 0;\n}\n"
    )
    assert output_file.read_text() == expected


def test_compile_single_parameter(tmp_path):
    src = "fn id(x: I32) => I32"
    input_file = tmp_path / "in.mg"
    input_file.write_text(src)
    output_file = tmp_path / "out.c"
    main(["-i", str(input_file), "-o", str(output_file)])
    expected = "int32_t id(int32_t x) {\n    return 0;\n}\n"
    assert output_file.read_text() == expected
