#include <stdio.h>
#include <stdlib.h>

#define NUM 10

int main()
{
    int i, j, data;

	int a[NUM];
	int b[NUM];

	for (i = 0;i < NUM;i++) 
	{
		a[i] = (rand() % NUM);
		for (j = 0;j < i;j++) 
		{
			if (a[i] == a[j]) 
			{
				i--;
			}
		}
	}
	
	printf("a :");
	for (i = 0;i < NUM;i++)
	{
		printf("%d ", a[i]);
		b[i] = a[i];
	}
	/*
	for (i = 0; i < NUM - 1; i++) 
	{
		for (j = i + 1; j < NUM; j++)
		{
			if (b[i] > b[j]) {
				data = b[i];
				b[i] = b[j];
				b[j] = data;
			}
		}
	}
	*/
	printf("\nb :");
	for (i = 0;i < NUM;i++)
	{
		printf("%d ", b[i]);
	}

	return 0;
}