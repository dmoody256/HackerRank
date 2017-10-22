import os
import subprocess

tests = []
for root, dirs, files in os.walk("./"):
    for file in files:
        filepath = os.path.join(root, file)
        buildDir = os.path.dirname(filepath)
        executable = os.path.basename(os.path.dirname(buildDir))

        if(buildDir.endswith("build") and file == executable ):
            testCommand = buildDir + "/" + executable
            print "Running tests for " + executable + "..."
            output = subprocess.check_output(testCommand)
            print output