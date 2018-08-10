#########################################################################
# File Name: make.sh
# Author: reus
#mail: dmarcoreus@1gmail.com
# Created Time:2018年08月07日 星期二 11时37分58秒
#########################################################################
#!/bin/bash

CC=g++ 
FLAGS=-g

for file_cpp in `ls *.cpp` ; 
do
	file_exe=`echo $file_cpp | awk -F. '{print $1}' | awk -F_ '{print $2}'`
	$CC $FLAGS $file_cpp -o $file_exe
done
