#!/bin/bash

#echo "1 2 3" >> numberr.txt

for ((i=0; i<151; i++))
do
od -vAn -N2 -tu2 < /dev/urandom >> numberr.txt
done