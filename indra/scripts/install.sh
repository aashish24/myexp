#!/bin/bash

if [ $# -ne 2 ] 
  then
    echo "Usage: $0 file dir"
    echo "copies file to the destination directory"
fi

file=$1
dir=$2
    
if [ -d $dir ] 
	then
	echo "$dir already exists";
else
	mkdir $dir
fi
		
echo "Copying $file"
cp -f $file $dir
echo done

