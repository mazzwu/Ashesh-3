// Yo winnie, i dont know if you remeber the asccii values
// of numbers ( i think i learnt in 1917)
// but this uses that 

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int main(int argc, char *argv[]){


char str[20];
  int i;
  printf("Enter any string->");
  scanf("%s",str);
  printf("The string is->%s",str);
  for(i=0;i<=strlen(str);i++){
      if(str[i]>=65&&str[i]<=90)
       str[i]=str[i]+32;
  }
  printf("\nThe string in lower case is->%s \n",str);

 

	return EXIT_SUCCESS; 
}

