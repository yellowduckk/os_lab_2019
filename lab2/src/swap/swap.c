#include "swap.h"
#include <stdio.h>

void Swap(char *left, char *right)
{
	char tmp;
	tmp = *left;
	*left = *right;
	*right = tmp;
	
}
