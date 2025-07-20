import os
import sys

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))

from magmac.__main__ import main


def test_main_output(capsys):
    main([])
    captured = capsys.readouterr()
    assert "Hello from Magmac!" in captured.out
