#!/usr/bin/python
import zipfile
import os
import sys
import fileinput

projectName = sys.argv[1]

with zipfile.ZipFile('ProjectTemplate.zip', "r") as z:
    extractPath = os.path.abspath(os.getcwd() + "/../" + projectName)
    z.extractall(extractPath)
    
    for line in fileinput.input(extractPath + "/SConstruct", inplace=True):
        sys.stdout.write(line.replace("PROJECT_TEMPLATE_NAME", projectName))
    