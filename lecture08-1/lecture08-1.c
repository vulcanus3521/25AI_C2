#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

struct Fish 
{
	char* name;

	char* talk;
	int answer;

	char* talk_O;
	char* talk_X;
};

int main() 
{
	srand((unsigned int)time(NULL));
	struct Fish fishList[5] = 
	{
		{"물고기", "1 : 공격 2 : 방어 3 : 도망", 2, "방어 맛있긴 해", "저런..."},
		{"불고기", "1 : 공격 2 : 방화 3 : 도망", 2, "불 올려라.", "그런..."},
		{"소고기", "1 : 공격 2 : 방어 3 : 도망 4 : 후원", 4, "사주셔서 감사합니다.", "결국..."},
		{"밥공기", "1 : 공격 2 : 방어 3 : 도둑", 3, "밥도둑 ㅇㅈ?", "어휴..."},
		{"콩고기", "1 : 회피 2 : 회피 3 : 회피", 0, "난 죽음을 택하겠다.", "정말..."}
	};
	printf("낚시찌를 던질까? ( Y / N ) > ");
	while (1)
	{
		char yn = _getch();
		if (yn == 'Y' || yn == 'y')
		{
			printf("%c\n", yn);
			for (int i = 0; i < 5; i++)
			{
				Sleep(500);
				printf(".");
			}
			break;
		}
		else if (yn == 'N' || yn == 'n') 
		{
			printf("%c\n", yn);
			printf("Game Over");
			return 0;
		}
	}

	int random = rand() % 5;

	printf("\n앗! 야생의 %s(이)가 나타났다!\n", fishList[random].name);
	printf("%s\n", fishList[random].talk);

	char select = _getch();
	printf("%c\n", select);

	if (select - 48 == fishList[random].answer)
	{
		printf("%s\n", fishList[random].talk_O);
	}
	else
	{
		printf("%s\n", fishList[random].talk_X);
	}

	return 0;
}
