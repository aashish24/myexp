
import string
import sys

def getPaths( config ): 
     # Storage
    paths = []

    # Flags    
    readSector  = 0
    readPaths   = 0
    
    # Open a config file and parse it. 
    f = open( config, 'r')

    for line in f:
            if string.rstrip(line) == string.upper("PATHS"):            
                readPaths += 1;        
            elif string.rstrip(line) == "{":
                readSector += 1
            elif string.rstrip(line) == "}":
                readSector -= 1
                if readPaths == 1:
                    readPaths -= 1
            # Read paths now. 
            elif readSector ==1 and readPaths == 1:
                paths.append( string.rstrip( ( string.lstrip( line ) ) ) )
                #line = string.rstrip( line ) + '/' + repoName 
                #paths.append( line )

    # Close the file
    f.close()
    
    return paths
    
