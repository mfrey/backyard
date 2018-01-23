i#!/usr/bin/env python

import cbor2 as cbor

def parse_file(path):
    with open(path, 'rb') as f:
        data = f.read()

        try:
            o = cbor.load(data)
        except Exception as e:
            sys.exit(1)

if __name__ == "__main__":
    path = sys.argv[1]
    parse_file(path)

    sys.exit(0)
