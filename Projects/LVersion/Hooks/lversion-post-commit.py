import os
import sys
import subprocess
from config_loader import *

REPOS   = sys.argv[1]
REV     = sys.argv[2] 

#print "Repository is: " REPOS " and Revision is: " REV

# @todo: Dump the changes to a file. 
# load the dump to sistes repos. 

# svnadmin dump %REPOS% -r %REV% --incremental > out.txt
# svnadmin load E:\aashish\TempTemp < out.txt

#for repos in paths: 
#    commit-email.pl repos "$REV" commit-watchers@example.org
#    log-commit.py --repository repos --revision "$REV"
path = REPOS + "\\" + "hooks"
os.chdir( path )
file = open( "out", "w" )
arg = REPOS + ' -r ' + REV + ' --incremental ' + ' > temp.txt'  
#p = subprocess.Popen( ["svnadmin", "dump", arg], stdout=None ) 
os.system( 'svnadmin dump ' + arg )
file.write( arg )
#file.close
#file = open( "temp", "w+" )
#file.write( p.communicate()[0] )
#file.close()

paths = getPaths( REPOS + '//lversion.cfg' )
file.write( ' '.join( paths ) )
file.close()
for i in paths: 
    arg = i + ' < temp.txt '
    os.system( 'svnadmin load ' + arg ) 
    #p = subprocess.POpen( ["svnadmin", "load", i + '<' + temp.txt], stdout=None )     