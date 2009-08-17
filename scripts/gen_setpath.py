
#
# \author Aashish Chaudhary
# \date   20090308
# 

# Global 
of = open('./setpaths.vbs','w')
paths = []

# Parse a given line, separate the var with its value and send
# both as arg to be written for the path. 
def parse(line):
    s = line.strip()
    index = s.find('=')    
    write_line(s[0:index], s[index+1:])
        

# Append var to environment variable. 
def write_line(var, var_value):    
    of.write('WshEnv("' + var + '")= ' + '"' + var_value + '"' + '\n')
    if(var.find('LIB') != -1 or var.find('BIN') != -1):
        #store all the paths here
        paths.append('WshEnv("' + var + '")')
        

# Open a file and set shell and environment. 
f = open('./paths.txt', 'r')
of.write('Set WSHShell = WScript.CreateObject("WScript.Shell")\n')
of.write('Set WshEnv = WshShell.Environment("SYSTEM")\n')

for line in f:
    parse(line)

# Now write the path environment variable.
of.write('WshEnv("PATH")=')
i = 0
for path in paths:
    if(i != 0):
        of.write(' & ' + path + ' & ";" ')        
    else:
        #of.write('WshEnv("PATH") & \";\" &' + path + ' & ";" ')
        of.write(path + ' & ";" ')
        i += 1
    
