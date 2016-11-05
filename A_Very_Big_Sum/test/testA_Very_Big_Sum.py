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

import unittest
#next section still working on

#def executeApplication():
#
#    def execute(proc):
#        stdout_lines = iter(proc.stdout.readline, "")
#        for stdout_line in stdout_lines:
#            yield stdout_line
#
#        proc.stdout.close()
#        return_code = proc.wait()
#
#    command = [os.path.abspath( os.path.join( self.buildDirectory, self.buildCommand ) )]
#    if self.buildArguments:
#        command.extend( self.buildArguments )
#
#    if platform.system() == 'Linux':
#        proc = subprocess.Popen(command, cwd=self.buildDirectory, stderr=subprocess.STDOUT, stdout=subprocess.PIPE)
#    else:
#        proc = subprocess.Popen(command, cwd=self.buildDirectory, stderr=subprocess.STDOUT, stdout=subprocess.PIPE, creationflags=subprocess.CREATE_NEW_PROCESS_GROUP)
#
#
#	for output in execute(proc):
#
#	    print(output.rstrip())
#            print("")
#            if(self.doingCommandLineBuild):
#                print("command line build")
#                continue
#            one_line_output = output.rstrip()
#            one_line_output_lower = one_line_output.lower()
#
#            try:
#                if "error:" in one_line_output_lower or "error :" in one_line_output_lower or ": error" in one_line_output_lower:
#                    editor.LogError( one_line_output )
#                elif "..." in one_line_output_lower:
#                    editor.LogInfo( one_line_output )
#                elif ProjectConfiguration.current.verboseBuildOutput:
#                    # Only logging every line if verbose has been selected
#                    editor.LogInfo( one_line_output )
#            except:
#                print "Exception logging output in",__file__
#                pass # Blocking the exception handling because throwing an exception here can deadlock the editor'''
#
#
#
#
#        # Check the result of the build
#        rval = proc.returncode;
#        success = False
#        if existingBuildProcess:
#            if rval != 0:
#                editor.LogError("Build failed; see log for details.")
#            else:
#                editor.LogInfo("Build succeeded.")
#                success = True
#        else:
#            pass # die quietly
#
#        return success


class KnownSums(unittest.TestCase):
    largeSums = [
        ['100000001', '100000002', '200000003'],
        ['1000000000001', '1000000000002', '2000000000003' ],
        ['10000000000000001', '10000000000000002', '20000000000000003' ],
        ['100000000000000000001', '100000000000000000002', '200000000000000000003' ],
        ['1000000000000000000000001', '1000000000000000000000002', '2000000000000000000000003' ],
        ['10000000000000000000000000001', '10000000000000000000000000002', '20000000000000000000000000003' ],
        ['100000000000000000000000000000001', '100000000000000000000000000000002', '200000000000000000000000000000003' ],
        ['10000000000000000000000000000000000000001', '10000000000000000000000000000000000000002', '20000000000000000000000000000000000000003' ],
        ['1000000000000000000000000000000000000000000000001', '1000000000000000000000000000000000000000000000002', '2000000000000000000000000000000000000000000000003' ],
        ['100000000000000000000000000000000000000000000000000000001', '100000000000000000000000000000000000000000000000000000002', '200000000000000000000000000000000000000000000000000000003' ],
        ['9999999999999999999999', '1', '10000000000000000000000' ],
        ['9999999999999999999999999999999999999999999999999', '1', '10000000000000000000000000000000000000000000000000' ],
        ['9999999999999999999999999999999999999999999999999', '9999999999999999999999999999999999999999999999999', '19999999999999999999999999999999999999999999999998' ],
        ['8070348572037465023476501862481273498126501982651', '2873465028736405826340562304985601986450198264051263', '2881535377308443291364038806848083259948324766033914']
    ]

class ValidInputs(unittest.TestCase):
    def testLargeValues(self):
        for(test in largeSums):

            self.assertEqual(test[2], result)

    def testSmallValues(self);
