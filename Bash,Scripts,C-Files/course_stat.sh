#!/bin/bash
# bash script that manage course statistics and grades

course_num=$1
if [[ ! $course_num =~ ^[0-9]+{6}$ ]]
  then 
     echo "Wrong number of arguments" >&2
     exit 1
     fi
 if [[ ! -f "$course_num".txt ]]
    then 
    echo "Course not found" >&2
    exit 1
   fi
   rm -r "$course_num"_stat
   mkdir "$course_num"_stat
 awk -F' ' '{print $2}' 044101.txt | grep -Eo [0-9]+ > grades.txt
 gcc -g -Wall calc_statistics.c -o prog.exe
 chmod 777 prog.exe
 ./prog.exe
cat course_statistics.txt
