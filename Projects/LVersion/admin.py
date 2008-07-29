
#!/usr/bin/python

#Author: Aashish Chaudhary  

# Basic imports
import os
import string 

# Boolean 
readSector = 0

# List of paths 
readPaths = 0

# Storage 
paths  = []

# Open a config file and parse it. 
f = open( 'repos.cfg' )
for line in f:
        if string.rstrip( line ) == string.upper("PATHS"):            
            readPaths = 1;        
        elif string.rstrip( line ) == "{":
            readSector = readSector + 1
        elif string.rstrip( line ) == "}":
            readSector = readSector - 1
        # Read paths now. 
        elif readSector ==1 and readPaths == 1:
            paths.append( line )
            
# Create repositories.             
for item in paths:
    os.system( 'svnadmin create' + item )
            
            
        
        