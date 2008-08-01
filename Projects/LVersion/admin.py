
#!/usr/bin/python

# Author: Aashish Chaudhary  

# Basic imports
import os
import string 
import sys
import subprocess

from config_loader import getPaths


def getDelimeter():
    if(sys.platform == "win32" or sys.platform == "win64"):
        return "\\"
    else:
        return '//'


def convertToNative(path): 
    if(sys.platform == "win32" or sys.platform == "win64"):
        return path.replace("/", "\\")
    else: 
        return path.replace("\", \"/")



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
    #f = open('Hooks/post-commit.py', 'r+')
    #lines = f.readlines()

    # Beginning of the file
    #f.seek(0)

    #f.write('paths=[')
    #f.write(",".join(paths))
    #f.write(']' + '\n')

    # Write old content 
    #f.write("".join( lines ))

    # Close the file. 
    #f.close()

    # Create repositories and copy hooks in the respective directories.                 
    for repoPath in paths:                            
        os.system( 'svnadmin create ' + repoPath )        
        hooksPath = repoPath + '/' + 'hooks'         
        os.system( 'cp -rf ./Hooks/* ' + hooksPath )     
        os.system( 'cp -f config_loader.py ' + hooksPath )         
        buildAndCopyConfig( repoPath, paths )

#
# Adding files to repository
#
# Get the lversion config for the current repos
# Switch to each repos
# run 'svn add'  
#
#////////////////////////////////////////////////////////////////////////////

def add(args):    
    delimiter = getDelimeter()    
    
    URL=""    
    addArgs = " ".join(args[2:len(args)])

    # @todo: 
    # Strip the file or directory name and keep the path.                
    slashIndex  = string.rfind(addArgs, delimiter)    
    svnInfoPath = addArgs[0 : slashIndex]
    addArgs     = addArgs[slashIndex : len(addArgs)]
        
    print "addArgs is: " + addArgs
    
    p = subprocess.Popen( ["svn", "info", svnInfoPath], stdout=subprocess.PIPE )
    info = p.communicate()[0]
    info =  info.split( "\n" )
    #print info
    for i in info:           
        #print i
        if string.rfind( i, "Repository Root" ) > -1:
            index = string.find( i, ":" )
            #print i
            #print index
            URL = string.strip( i[index + 1 : len( i )] )                
            print "URL is: " + URL
            
            # Now we have the URL read the config and switch to repositories accordingly.             
            if string.find(URL, "file:///") > -1: 
                repoPath = URL.strip("file:///")
                repoPath = convertToNative( repoPath )                
                print repoPath
                print repoPath + delimiter + 'lversion.cfg'
                repoPaths = getPaths( repoPath + delimiter + 'lversion.cfg')
                #print repoPaths   
                for i in repoPaths: 
                    print i
                    # @todo: Fix writing path to the config. 
                    #subprocess.Popen(["svn", "switch" "URL"], i)
                    #subprocess.Popen(["svn", "add"], addArgs)
                
    
#
# Parase command line. 
# @todo: Read the last argument for REPO_PATH and also should be able to pass 
# the arguments. 
#
#////////////////////////////////////////////////////////////////////////////

for args in sys.argv:
    if args == "create": 
        code = create(sys.argv[2])
    
    # @note: We have a different stratagey now. We will use svn dump as of now. 
    #if args == "add":        
    #    code = add( sys.argv )
        
