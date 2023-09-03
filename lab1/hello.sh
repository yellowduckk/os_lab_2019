#!/bin/bash

echo "текущий путь: $( dirname -- "$( readlink -f -- "$0"; )"; )"

echo "сегодня: " `date`

echo "соедержимое перменное окружения PATH:" $PATH
