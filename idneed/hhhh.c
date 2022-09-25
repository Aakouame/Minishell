#include <stdio.h>

void  hey(int a, int b, int g, int k, int l)
{
  printf("%d, %d, %d, %d, %d", a, b ,g ,k, l);
}

int main(void)
{
  int a = 4;
  int b = 4;
  int g = 4;
  int k = 4;
  int l = 4;
  hey(a, b, g, k, l);
}
