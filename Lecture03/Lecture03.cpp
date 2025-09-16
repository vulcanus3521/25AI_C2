#include <stdio.h>

void sum(int x, int y, int *re)
{
    *re = x + y;
}

int main()
{
    int a = 3;
    int b = 2;
    int c = 0;

    /*int* pa;
    pa = &a;
    printf("%d", *pa);
    */

    sum(a, b, &c);

    printf("%d", c);

    return 0;
}
