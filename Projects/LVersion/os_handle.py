
# Author: Aashish Chaudhary
#
# This module will provide functionality to support various OS related operations
#

import sys

def getDelimeter():
    if(sys.platform == "win32" or sys.platform == "win64"):
        return "\\"
    else:
        return '//'

