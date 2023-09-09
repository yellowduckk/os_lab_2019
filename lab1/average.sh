#!/bin/bash

#echo "Кол-во параметров:" $#
echo "Введено: $@"

count=0
sum=0

while read param
do

count=$(($count+1))
sum=$(($sum+$param))

done

echo "Кол-во элементов: " $count
echo "сумма: " $sum

let "sred=$sum/$count"
echo "Среднее арифметическое: $sred"