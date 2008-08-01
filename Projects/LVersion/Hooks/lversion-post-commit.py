import os
import sys
import subprocess
from import config_loader *

REPOS   = sys.argv[1]
REV     = sys.argv[2] 

print "Repository is: " REPOS " and Revision is: " REV

# @todo: Dump the changes to a file. 
# load the dump to sistes repos. 

# svnadmin dump %REPOS% -r %REV% --incremental > out.txt
# svnadmin load E:\aashish\TempTemp < out.txt

#for repos in paths: 
#    commit-email.pl repos "$REV" commit-watchers@example.org
#    log-commit.py --repository repos --revision "$REV"

p = subprocess.POpen( ["svnadmin", "dump", REPOS + '-r' + REV + '--incremental'], stdout=subprocess.PIPE ) 
file = open( "temp", "w+" )
file.write( p.communicate()[0] )
file.close()

paths = getPaths( '..//lversion.cfg' )
print paths 
for i in paths: 
    p = subprocess.POpen( ["svnadmin", "load", i + '<' + file], stdout=subprocess.PIPE )     