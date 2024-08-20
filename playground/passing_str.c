#include <stdio.h>

void change_str(char *str)
{
  str[0] = 'a';
  printf("inside %s\n", str);
}

int main(void)
{
  char str_ori[] = "hello";
  change_str(str_ori);
  printf("ori %s\n", str_ori);
  return 0;
}
