#!/usr/bin/env python3

import io
import os
import os.path
import subprocess
import sys

from os import listdir
from time import strftime

BASE_DIR = os.path.dirname(os.path.realpath(__file__))
PARSERS_DIR = os.path.join(BASE_DIR, "parsers")

programs = {
    "flynn" : 
    {
        "url":"https://github.com/fritz0705/flynn",
#        "commands":[os.path.join(PARSERS_DIR, "test_flynn_CBOR/CBOR.sh")],
        "use_stdin":True
    },

    "Python cbor (py3)": # pip install cbor
    {
        "url":"https://pypi.python.org/pypi/cbor",
        "commands":["/usr/bin/env", "python3.5", os.path.join(PARSERS_DIR, "test_cbor.py")]
    },

    "Python cbor2 (py3)": # pip install cbor2
    {
        "url":"https://pypi.python.org/pypi/cbor2",
        "commands":["/usr/bin/env", "python3.6", os.path.join(PARSERS_DIR, "test_cbor2.py")]
    },

    "Python pycbor (py3)": # pip install pycbor
    {
        "url":"https://pypi.python.org/pypi/cbor2",
        "commands":["/usr/bin/env", "python3", os.path.join(PARSERS_DIR, "test_pycbor.py")]
    }
}


#if __name__ == '__main__':


#    import argparse
#    parser = argparse.ArgumentParser()
