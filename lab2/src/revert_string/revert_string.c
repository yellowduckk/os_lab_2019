#include "revert_string.h"
#include <stdio.h>

void RevertString(char *str)
{
	// your code here
  int len=0, n;
  char temp;
 // len=strlen(str);
  
  
  for (int i = 0; str[i] != '\0'; i++){
      len = i;
      n = i;
  }
  len += 1;
// printf("%d %d", len, n);
  int a =5;
  
   for(int i = 0; i <=(len/2); i++)
  {
    temp=str[i];
    str[i]=str[n];
    str[n]=temp;
    n--;
  }
  
  for (int i =0; i<len; i++){
      printf("%c", str[i]);
  }
}

