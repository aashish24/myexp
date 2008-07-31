
#!/usr/bin/python

# Author: Aashish Chaudhary  

# Basic imports
import os
import string 
import sys

from config_loader import getPaths

def buildAndCopyConfig( repoPath="", paths=[] ):
    # Check for NULL args.
        
    # Get all the paths. 
    
    #repoPath = string.lstrip(repoPath)
    #repoPath = string.rstrip(repoPath)
    
    fullPath = repoPath + '/' + "lversion.cfg"
    print fullPath
    f = open( fullPath, 'w' )
    f.write( "PATHS \n { \n" )
    f.write( "\n".join( paths ) )
    f.write( "\n } \n" )
    f.close()

#
# Create a repository.
#
#////////////////////////////////////////////////////////////////////////////

def create( repoName="", config="repos.cfg" ): 
    
    if repoName ==  "" or config == "": 
        return -1
       
    # Write paths
    paths = getPaths( config )
    for i in range( 0, len( paths ) ):
        paths[i] = paths[i] + '/' + repoName
        #print paths
        
    # Copy path names to the hooks
    # @todo: Make it more efficient 
    
    # First read existing lines.  
    f = open('Hooks/post-commit.py', 'r+')
    lines = f.readlines()

    # Beginning of the file
    f.seek(0)

    f.write('paths=[')
    f.write(",".join(paths))
    f.write(']' + '\n')

    # Write old content 
    f.write("".join( lines ))

    # Close the file. 
    f.close()

    # Create repositories and copy hooks in the respective directories.                 
    for repoPath in paths:                            
        os.system( 'svnadmin create ' + repoPath )        
        hooksPath = repoPath + '/' + 'hooks'         
        os.system( 'cp -rf ./Hooks/* ' + hooksPath )     
        buildAndCopyConfig( repoPath, paths )

#
# Adding files to repository
#
# Get the lversion config for the current repos
# Switch to each repos
# run 'svn add'  
#
#////////////////////////////////////////////////////////////////////////////

#def add( args ):     
    
#
# Parase command line. 
# @todo: Read the last argument for REPO_PATH and also should be able to pass 
# the arguments. 
#
#////////////////////////////////////////////////////////////////////////////

for args in sys.argv:
    if args == "create": 
        code = create(sys.argv[2])
    if args == "add":        
        code = add( sys.argv )
        
