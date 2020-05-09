#!/usr/bin/env python
# encoding=utf-8

from __future__ import print_function
import os


def main():
    filename = os.path.join(os.environ['MESON_SOURCE_ROOT'], 'VERSION')
    with open(filename) as f:
        version = f.read().strip()
    print(version, end='')


if __name__ == '__main__':
    main()
