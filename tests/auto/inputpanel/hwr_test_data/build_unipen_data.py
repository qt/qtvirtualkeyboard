#!/usr/bin/env python

# Copyright (C) 2017 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

import os
import sys
import json
import datetime
import getopt
import re

unipen_file_pattern = re.compile(r'(^[0-9]{2,9}).*\.txt')

def print_header():
    print """
// Copyright (C) %s The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0
""" % datetime.datetime.now().year

def scan_unipen_files(path):
    file_list = []
    for root, dirs, files in os.walk(path):
        for name in files:
            if unipen_file_pattern.match(name):
                file_list.append(os.path.join(root, name))
    return file_list

def help():
    sys.exit("""Command line tool for converting Unipen files to JavaScript.

Usage: %s [dir1] .. [dirX]

Scans given directories recursively for Unipen text files and converts
them into JavaScript format. The result is printed to the stdout.

The Unipen file name must start with the Unicode character encoded in decimal
format, and end with .txt extension.""" % sys.argv[0])

def main():
    if len(sys.argv) < 2:
        help()

    # Collect arguments
    opts, args = getopt.getopt(sys.argv[1:], '', [])

    # Build a list of Unipen files in directories
    file_list = []
    for arg in args:
        if not os.path.exists(arg):
            sys.exit("Error: no such directory " + arg)
        file_list.extend(scan_unipen_files(arg))

    # Scan the Unipen files and build a data structure
    unipen_map = {}
    for file_name in file_list:
        lines = tuple(open(file_name, 'r'))
        unipen_data = {}
        pen_data = []
        for line in lines:
            line = line.strip()
            if not line:
                continue
            if line.startswith('.'):
                parts = line.split(' ')
                if len(parts) > 2:
                    unipen_data[parts[0]] = parts[1:]
                elif len(parts) == 2:
                    unipen_data[parts[0]] = int(parts[1]) if parts[1].isdigit() else parts[1]
                elif len(parts) == 1:
                    if parts[0] == '.PEN_DOWN':
                        if not unipen_data.has_key('.PEN'):
                            unipen_data['.PEN'] = []
                        pen_data = []
                    elif parts[0] == '.PEN_UP':
                        unipen_data['.PEN'].append(pen_data)
            else:
                pen_data.append([int(coord) for coord in line.split(' ')])
        file_name_match = unipen_file_pattern.match(os.path.basename(file_name))
        unipen_map["0x%04x" % int(file_name_match.groups()[0])] = unipen_data

    # Convert to json format and print to stdout
    print_header()
    print
    print 'var unipenData = ' + json.dumps(unipen_map, indent=4, separators=(',', ': '), sort_keys=True)

if __name__ == '__main__':
    main()

