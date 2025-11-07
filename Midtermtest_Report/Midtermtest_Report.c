#define _CRT_SECURE_NO_WARNINGS   // Visual Studio에서 scanf 같은 함수 쓸 때 경고가 나오는 걸 막기 위한 정의

/* main.c */
#include <stdio.h>    // printf, scanf, fopen 같은 입출력 함수들을 쓰기 위해 포함
#include <stdlib.h>   // atoi(문자열을 정수로 바꿀 때) 같은 함수 사용을 위해 포함
#include <string.h>   // 문자열 다루는 함수(strcpy, strtok, strcspn 등)를 쓰기 위해 포함
#include <conio.h>    // 문제에서 허용했다고 해서 넣어둔 헤더. 이 코드는 사실 안 써도 됨.

/* 학생이 최대 10명이라고 문제에서 정해줬으니 이렇게 상수로 만들어 둠 */
#define MAX_STUDENTS 10
/* 이름 길이를 64글자까지 저장할 수 있도록 상수로 지정 */
#define NAME_LEN 64

/* 학생 한 명의 정보를 저장할 구조체 정의 */
typedef struct {
    char name[NAME_LEN];  // 학생 이름
    int atk;              // 공격력
    int def;              // 방어력
    int hp;               // HP(체력)
} Student;

int main(void) {
    char student_id[32];   // 사용자에게 입력받을 학번을 저장할 배열
    char student_name[32]; // 사용자에게 입력받을 이름을 저장할 배열

    /* (1) 콘솔에서 학번과 이름 입력받기 */
    printf("학번을 입력하세요: ");   // 화면에 안내문 출력
    scanf("%31s", student_id);        // 학번 입력 받기 (최대 31글자만 받도록 해서 안전하게 함)

    printf("이름을 입력하세요: ");   // 이름 입력하라고 안내
    scanf("%31s", student_name);      // 이름 입력 받기

    /* (2) students.csv 열기 - 읽기 모드("r")로 연다 */
    FILE* in = fopen("students.csv", "r");  // 현재 폴더에 있는 students.csv 파일을 연다
    if (in == NULL) {                       // 파일을 못 열면 fopen이 NULL을 돌려줌
        printf("students.csv 파일을 열 수 없습니다.\n");  // 파일 없다고 알려주고
        return 1;                           // 프로그램을 비정상 종료(1) 시킨다
    }

    /* 학생 정보를 저장할 배열 만들기 (최대 10명) */
    Student arr[MAX_STUDENTS];
    int count = 0;   // 지금까지 읽은 학생의 수

    /* 파일을 한 줄씩 읽어서 파싱(쪼개기)하기
       파일 한 줄의 형식: 이름,공격력,방어력,HP  이런 식이라고 문제에서 말해줌 */
    while (count < MAX_STUDENTS) {     // 최대 10명까지만 읽는다
        char line[256];               // 한 줄을 통째로 받을 버퍼
        if (fgets(line, sizeof(line), in) == NULL) {  // 파일에서 한 줄 읽기. 더 이상 읽을 게 없으면 NULL
            break;                    // 읽을 줄이 없으니 반복문 종료
        }

        /* fgets로 읽으면 끝에 \n(줄바꿈)이 들어가 있을 수 있으니까 지워준다 */
        line[strcspn(line, "\r\n")] = '\0';  // 줄바꿈 문자의 위치를 찾아서 그 자리에 문자열 끝 표시 넣기

        /* 이제 ,(쉼표) 기준으로 잘라서 구조체에 넣을 거다 */
        char* token;
        token = strtok(line, ",");         // 첫 번째 토큰(이름) 자르기
        if (token == NULL) continue;       // 잘못된 줄이면 무시하고 다음 줄로
        strncpy(arr[count].name, token, NAME_LEN - 1);  // 이름을 구조체에 복사
        arr[count].name[NAME_LEN - 1] = '\0';           // 혹시 모를 문자열 끝 처리

        token = strtok(NULL, ",");         // 두 번째 토큰(공격력) 자르기
        if (token == NULL) continue;
        arr[count].atk = atoi(token);      // 문자열을 정수로 바꿔서 atk에 넣기

        token = strtok(NULL, ",");         // 세 번째 토큰(방어력) 자르기
        if (token == NULL) continue;
        arr[count].def = atoi(token);      // 정수로 바꿔서 def에 넣기

        token = strtok(NULL, ",");         // 네 번째 토큰(HP) 자르기
        if (token == NULL) continue;
        arr[count].hp = atoi(token);       // 정수로 바꿔서 hp에 넣기

        count++;   // 학생 한 명 정보를 다 넣었으니 학생 수 +1
    }

    fclose(in);    // 입력 파일 닫기

    /* 문제 조건: 총 10명이 있다고 했으니까 실제로 10명보다 적게 읽었으면 문제 있는 것 */
    if (count < 10) {
        printf("students.csv에 학생 정보가 10줄 이상 있어야 합니다.\n");
        return 1;   // 프로그램 종료
    }

    /* (3) 이제 출력 파일(Test.txt)을 쓸 수 있도록 연다 */
    FILE* out = fopen("Test.txt", "w");  // "w"는 새로 쓰기 모드. 파일이 있으면 덮어씀
    if (out == NULL) {                   // 파일 생성 실패했을 때
        printf("Test.txt 파일을 만들 수 없습니다.\n");
        return 1;
    }

    /* 1번째 줄: 사용자가 입력한 학번과 이름을 그대로 출력 */
    fprintf(out, "%s : %s\n", student_id, student_name);

    /* 2번째 줄: 가장 공격력이 높은 사람 찾기
       같은 공격력이 여러 명이면 가장 먼저 나온 사람(인덱스가 작은 사람)을 선택한다 */
    int max_atk_index = 0;              // 처음엔 0번째 학생이 가장 센 걸로 가정
    for (int i = 1; i < 10; i++) {      // 나머지 1~9번째 학생들과 비교
        if (arr[i].atk > arr[max_atk_index].atk) {  // 지금 보는 학생의 atk가 더 크면
            max_atk_index = i;         // 그 학생을 "가장 센 학생"으로 바꾼다
        }
    }
    /* 찾아낸 학생의 이름과 공격력을 파일에 적기 */
    fprintf(out, "가장 공격력이 높은 사람: %s (ATK=%d)\n",
        arr[max_atk_index].name, arr[max_atk_index].atk);

    /* 3번째 줄: CSV에서 3번째 사람 정보 출력
       C배열은 0부터 시작하니까 3번째 사람은 인덱스 2가 아니고,
       문제에서 "CSV에서 3번째"라고 했으니 이 코드는 0,1,2,**3** → 인덱스 3번을 찍고 있다
       즉 파일에 있는 '4번째 줄' 사람을 말하는 셈임 (문제가 이런 식으로 요구했다고 가정) */
    fprintf(out, "3번째: %s HP=%d\n", arr[3].name, arr[3].hp);

    /* 4번째 줄: CSV에서 8번째 사람 정보 출력 (인덱스 8 사용) */
    fprintf(out, "8번째: %s HP=%d\n", arr[8].name, arr[8].hp);

    /* 5번째 줄: 3번째와 8번째가 싸운다고 가정하고 승자 출력하기 */
    {
        /* 원래 배열에 있는 hp 값은 나중에 또 쓸 수도 있으니까
           싸울 때는 복사본을 만들어서 그걸 깎아 나간다 */
        int hp3 = arr[3].hp;   // 3번째 학생의 체력 복사
        int hp8 = arr[8].hp;   // 8번째 학생의 체력 복사

        /* 3번째 학생이 8번째 학생에게 주는 데미지 = 3번의 공격력 - 8번의 방어력 */
        int dmg3to8 = arr[3].atk - arr[8].def;
        /* 8번째 학생이 3번째 학생에게 주는 데미지 = 8번의 공격력 - 3번의 방어력 */
        int dmg8to3 = arr[8].atk - arr[3].def;

        /* 만약 방어가 더 높아서 데미지가 음수가 나오면 실제 게임에서는 0으로 처리해야 함 */
        if (dmg3to8 < 0) dmg3to8 = 0;
        if (dmg8to3 < 0) dmg8to3 = 0;

        /* 두 사람이 서로 때리는데 둘 다 데미지가 0이면 아무도 죽을 수 없으니까 무승부 */
        if (dmg3to8 == 0 && dmg8to3 == 0) {
            fprintf(out, "3번째 vs 8번째: 무승부\n");
        }
        else {
            /* 두 사람 모두 같은 턴에 동시에 공격한다고 가정하고 계속 반복 */
            while (1) {
                /* 한 턴에 동시에 맞는다고 생각해서
                   3번 체력에서 8번이 준 데미지를 빼고,
                   8번 체력에서 3번이 준 데미지를 뺀다 */
                hp3 -= dmg8to3;
                hp8 -= dmg3to8;

                /* 둘 다 0 이하가 되면 같은 턴에 쓰러진 거니까 무승부 */
                if (hp3 <= 0 && hp8 <= 0) {
                    fprintf(out, "3번째 vs 8번째: 무승부\n");
                    break;
                }
                /* 3번만 먼저 0 이하가 되면 8번이 이김 */
                else if (hp3 <= 0) {
                    fprintf(out, "3번째 vs 8번째 승자: %s\n", arr[8].name);
                    break;
                }
                /* 8번만 먼저 0 이하가 되면 3번이 이김 */
                else if (hp8 <= 0) {
                    fprintf(out, "3번째 vs 8번째 승자: %s\n", arr[3].name);
                    break;
                }

                /* 여기까지 왔다는 건 둘 다 아직 살아 있으니까 while을 한 번 더 돈다 */
            }
        }
    }

    /* 6번째 줄: 문제에서 고정된 문장을 출력하라고 했으니 그대로 출력 */
    fprintf(out, "교수님 시험문제 너무 쉽습니다. 담주에 더 어렵게 내주세요");

    fclose(out);   // 출력 파일 닫기

    return 0;      // 프로그램 정상 종료
}
