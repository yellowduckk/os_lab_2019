#!/bin/bash

#echo "1 2 3" >> numberr.txt

for ((i=0; i<10; i++))
do
echo $((1 + $RANDOM % 100)) >> numberr.txt
done