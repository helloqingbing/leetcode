/* sscanf example */
#include <stdio.h>


char* dumpStr() 
{
    char *str = "hello,world";
    return str;
}

int main ()
{
  char sentence []="Rudolph is 12 years old";
  char str [20];
  int i;

  int ret = sscanf (sentence,"%s %*s %d",str,&i);
  printf ("%s -> %d\n",str,i);
  printf ("%d\n",ret);
  int arr[] = {6, 7, 8, 9};
  int *ptr = arr;
  printf("%d\n", *ptr);
  printf("%d, %d\n", *ptr, *(++ptr));
  char* myStr = dumpStr();  
  printf("%s\n", myStr);
  char ch = 128;
  printf("%d\n", ch);
  return 0;
}
