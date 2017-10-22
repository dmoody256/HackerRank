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

AddOption(
        '--unit-test',
        dest='test_build',
        action='store_true',
        metavar='DIR',
        default=False,
        help='Build in test mode'
    )

warmupDir = "Warmup"
sortingDir = "Sorting"

builds = SConscript([
    warmupDir + '/A_Very_Big_Sum/SConstruct',
    warmupDir + '/Diagonal_Difference/SConstruct',
    warmupDir + '/Plus_Minus/SConstruct',
    warmupDir + '/Staircase/SConstruct',
    warmupDir + '/Time_Conversion/SConstruct',    
    warmupDir + '/Circular_Array_Rotation/SConstruct',
    sortingDir + '/The_Full_Counting_Sort/SConstruct',
    sortingDir + '/Closest_Numbers/SConstruct',
    sortingDir + '/Find_the_Median/SConstruct',
    sortingDir + '/Insertion_Sort_Advanced_Analysis/SConstruct',
])

runTests = GetOption('test_build')

if(runTests == True):
    com = Command("neverexist.file", None, 'python UtilScripts/run_tests.py')