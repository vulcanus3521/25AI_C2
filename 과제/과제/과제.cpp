#include<math.h>
#include<stdio.h>
#include<Windows.h>

int gotoxy(int x, int y) 
{
	printf("\033[%d;%dH", y, x);
	return 0;
}

int END(int x, int y)
{
	gotoxy(0, 0);
	printf("^^^^^^\n");
	printf("!BOOM!\n");
	printf("^^^^^^");
	return 0;
}

int main() 
{
	
	double PI = 3.141592653/*58979323846*/;
	
	printf("(B)");
	int a = 6;
	int posx = 3, posy = 1;
	int x, y;
	double angle = 0.0;
	int length = a;


	while (length > 0)
	{
		
		/*gotoxy(15, 5);
		printf("%0f", angle);*/

		x = cos(angle * PI / 180.0);
		y = sin(angle * PI / 180.0);
		int count = 0;
		while (count < length)
		{
			posx += x;
			posy += y;
			gotoxy(posx, posy);
			if (count == length - 1) 
			{ 
				Sleep(100); 
				printf("+"); 
			}
			else 
			{
				Sleep(100);
				printf("-");
			}
			count++;
		}
		angle += 90.0;

		/*gotoxy(15, 5);
		printf("%0f", angle);*/

		x = cos(angle * PI / 180.0);
		y = sin(angle * PI / 180.0);
		length--;
		count = 0;
		while (count < length)
		{
			posx += x;
			posy += y;
			gotoxy(posx, posy);
			if (count == length - 1)
			{
				Sleep(100);
				printf("+"); 
			}
			else 
			{ 
				Sleep(100);
				printf("|"); 
			}
			count++;
		}
		angle += 90.0;

		/*gotoxy(15, 5);
		printf("%0f", angle);*/
	}

	gotoxy(posx, posy);
	printf("*");
	Sleep(300);

	angle -= 180.0;

	while (length < a) 
	{
		angle -= 90.0;

		/*gotoxy(15, 5);
		printf("%0f", angle);*/
		
		x = cos(angle * PI / 180.0);
		y = sin(angle * PI / 180.0);
		int count = 0;
		while (count < length)
		{
			Sleep(100);
			gotoxy(posx, posy);
			printf(" ");
			posx += x;
			posy += y;
			gotoxy(posx, posy);
			printf("*");
			count++;
		}
		angle -= 90.0;

		/*gotoxy(15, 5);
		printf("%0f", angle);*/

		x = cos(angle * PI / 180.0);
		y = sin(angle * PI / 180.0);
		length++;
		count = 0;
		while (count < length)
		{
			Sleep(100);
			gotoxy(posx, posy);
			printf(" ");
			posx += x;
			posy += y;
			gotoxy(posx, posy);
			if (length != a + 1) printf("*");
			count++;
		}
	}

	END(posx, posy);
	gotoxy(0, 10);
	return 0;
}