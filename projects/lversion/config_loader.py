
import string
import sys

def getPaths( config ): 
    print config
    
     # Storage
    paths = []

    # Flags    
    readSector  = 0
    readPaths   = 0
    
    # Open a config file and parse it. 
    f = open( config, 'r')

    for line in f:
            #print line
            if string.strip(line) == string.upper("PATHS"):            
                #print line
                readPaths += 1;                    
            elif string.rstrip(line) == "{":
                #print line
                readSector += 1
            elif string.rstrip(line) == "}":
                #print line
                readSector -= 1
                if readPaths == 1:
                    readPaths -= 1
            # Read paths now. 
            elif readSector ==1 and readPaths == 1:
                #print line
                paths.append( string.strip( line ) )                

    # Close the file
    f.close()
    
    return paths
    
