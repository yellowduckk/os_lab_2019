#!/bin/bash

#echo "Кол-во параметров:" $#
echo "Введено: $@"

for param in $@
do
#echo "\$@ Parameter #$count = $param"
sum=$(( $sum + $param))
count=$(( $count + 1 ))
done

echo "Кол-во элементов: " $count
echo "сумма: " $sum
let "sred=$sum/$count" 

echo "Среднее арифметическое: $sred"
#mycommand "$(< file.txt)"