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
import sys
import platform
import subprocess

def executeApplication(abspathExecutable, stdin):

    appDir = os.path.dirname(abspathExecutable)
    outputResult = ""
    def execute(proc):
        stdout_lines = iter(proc.stdout.readline, "")
        for stdout_line in stdout_lines:
            yield stdout_line

        proc.stdout.close()
        return_code = proc.wait()

    if platform.system() == 'Linux':
        proc = subprocess.Popen(abspathExecutable,
                                cwd=appDir,
                                stdin=subprocess.PIPE,
                                stderr=subprocess.PIPE,
                                stdout=subprocess.PIPE)
    else:
        proc = subprocess.Popen(abspathExecutable,
                                cwd=appDir,
                                stdin=subprocess.PIPE,
                                stderr=subprocess.PIPE,
                                stdout=subprocess.PIPE,
                                creationflags=subprocess.CREATE_NEW_PROCESS_GROUP)

    stdout_data = proc.communicate(input=stdin)[0]

    return stdout_data
