#########################################################################
# File Name: make.sh
# Author: reus
#mail: dmarcoreus@1gmail.com
# Created Time:2018年08月07日 星期二 11时37分58秒
#########################################################################
#!/bin/bash

CC=g++ 
FLAGS=-g

clean=$1
case $clean in
	"clean")
		echo "rm -rf app_*"
		rm -rf app_*
		exit 0 ;;
	*) ;;
esac

for file_cpp in `ls *.cpp` ; 
do
	file_exe=`echo $file_cpp | awk -F. '{print $1}' | awk -F_ '{print $2}'`
	echo "$CC $FLAGS $file_cpp -o app_$file_exe"
	$CC $FLAGS $file_cpp -o app_$file_exe
done
