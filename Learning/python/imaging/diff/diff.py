#!/usr/bin/python

#
# \author Aashish Chaudhary
#
# This program creates a true difference image. 
#

# Python modules. 
import os, sys
import Image
import glob 
import getopt

from Numeric import *

# Requires PIL module(not present by default).
import ImageChops

threshold   = 0
outdir      = "./outdir"
source      = "./source"
comparison  = "./comparison"

opts, args = getopt.getopt(sys.argv[1:], "t:s:c:o:", ["threshold=", "source=", "comparison=", "outdir="])
for opt, arg, in opts:
  if opt == "-t":
    threshold = int(arg)
  elif opt in ("-o", "--outdir"):
    outdir = arg 
  elif opt in ("-s", "--source"):
    source = arg
  elif opt in ("-c", "--comparison"):
    comparison = arg    
      

print "Threshold is: ", threshold

L1 = os.listdir(source)
for item in L1:
  print item

# Using ImageChops module. 
#for item in L1:
  #im1 = Image.open("./sph-images" + "/" + item)
  #im2 = Image.open("./vrj-images" + "/" + item)
  #im3 = ImageChops.difference(im1, im2)  
  #filename  = "./diffs" + "/" + item + ".jpg"     
  #print "writing file " + filename
  #im3.save(filename)

# Now create the output dir.
if os.path.exists(outdir) == False: 
  os.mkdir(outdir)

# Custom code. 
for item in L1: 
  im1 = Image.open(source + "/" + item)
  im2 = Image.open(comparison + "/" + item)       
  imageSize = im1.size
  #print imageSize[0]
  #print imageSize[1]
  width   = imageSize[0] - 1
  height  = imageSize[1] - 1  
  im3 = Image.new("RGBA",(imageSize[0],imageSize[1]))  
  for i in range(0, width):
    for j in range(0, height):
      #print i
      #print j          
      pixel1 = im1.getpixel((i,j))      
      pixel2 = im2.getpixel((i,j))
      #print pixel1
      #print pixel2
      R = abs(pixel1[0] - pixel2[0])
      G = abs(pixel1[1] - pixel2[1])
      B = abs(pixel1[2] - pixel2[2])        
       
      #print "R is"
      #print R
      #print "G is"
      #print G
      #print "B is" 
      #print B        
      
      if R <= threshold:        
        R = 0   
                           
      if G <= threshold:        
        G = 0
        
      if B <= threshold:
        B = 0  
                                     
      im3.putpixel((i,j), (R, G, B, 1))
      
  filename  = outdir + "/" + item + ".jpg"     
  print "writing file " + filename
  im3.save(filename)
  