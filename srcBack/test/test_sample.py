import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
# allows us to import python files in parent directory
# EG
import main


def func(x):
    return x + 1


def test_answer():
    assert func(3) == 5
