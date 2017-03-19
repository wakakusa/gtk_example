#include <stdio.h>

int main(void)
{
  int a,b,c;

  printf("Please a\n");
  scanf("%d",&a);

  printf("Please b\n");
  scanf("%d",&b);
  
  c=add(a,b);
  printf("c = a:%d + b:%d = %d\n",a,b,c);
  
  return 0;
}
