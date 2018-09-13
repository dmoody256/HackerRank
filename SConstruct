# This file is licensed under the MIT License.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

import os
import json
import sys
import glob
import itertools

AddOption(
        '--unit-test',
        dest='test_build',
        action='store_true',
        metavar='DIR',
        default=False,
        help='Build in test mode'
    )

for root, dirs, files in itertools.chain(os.walk("Sorting"), os.walk("Warmup"), os.walk("Strings")):
    for file in files :
        if os.path.basename(file) == "SConstruct" :
            #print("appending " + os.path.join(root, file))
            SConscript(os.path.join(root, file))

runTests = GetOption('test_build')

if(runTests == True):
    com = Command("neverexist.file", None, 'python UtilScripts/run_tests.py')