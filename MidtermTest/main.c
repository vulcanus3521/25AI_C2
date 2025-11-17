#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>  // 사용은 안 하지만, 문제에서 허용 헤더라 포함

#define MAX_STUDENTS 200
#define MAX_NAME_LEN 64

typedef struct {
    char name[MAX_NAME_LEN];
    int atk;
    int def;
    int hp;
    int mp;
} Student;

/*
 * a와 b가 1:1 전투를 한다.
 * 반환값:  1  = a 승
 *          0  = 무승부
 *         -1  = b 승
 */
int battle(const Student* A, const Student* B)
{
    int hpA = A->hp;
    int hpB = B->hp;
    int mpA = A->mp;
    int mpB = B->mp;
    int atkA = A->atk;
    int atkB = B->atk;
    int defA = A->def;
    int defB = B->def;

    /* 무한 루프 방지를 위한 안전 장치 (충분히 큰 수) */
    int turn;
    for (turn = 0; turn < 100000; ++turn) {
        int atkPointA, atkPointB;
        int dmgToA, dmgToB;

        /* A의 공격 포인트 및 MP 처리 */
        if (mpA >= atkA) {
            mpA -= atkA;
            atkPointA = atkA;
        }
        else {
            mpA += 10;
            atkPointA = atkA / 2;
        }

        /* B의 공격 포인트 및 MP 처리 */
        if (mpB >= atkB) {
            mpB -= atkB;
            atkPointB = atkB;
        }
        else {
            mpB += 10;
            atkPointB = atkB / 2;
        }

        /* 실제 피해량 계산 (방어력 반영) */
        dmgToA = atkPointB - defA;
        if (dmgToA < 0) dmgToA = 0;

        dmgToB = atkPointA - defB;
        if (dmgToB < 0) dmgToB = 0;

        /* 양쪽 피해가 모두 0이면 즉시 무승부 */
        if (dmgToA == 0 && dmgToB == 0) {
            return 0;
        }

        /* 동시에 피해 적용 */
        hpA -= dmgToA;
        hpB -= dmgToB;

        /* 둘 다 같은 턴에 죽으면 무승부 */
        if (hpA <= 0 && hpB <= 0) {
            return 0;
        }
        /* B가 먼저 0 이하 → A 승리 */
        if (hpB <= 0) {
            return 1;
        }
        /* A가 먼저 0 이하 → B 승리 */
        if (hpA <= 0) {
            return -1;
        }
    }

    /* 이론상 여기까지 오지 않아야 하지만,
       혹시라도 도달하면 무승부 처리 */
    return 0;
}

int main(void)
{
    FILE* fpIn = NULL;
    FILE* fpOut = NULL;
    Student students[MAX_STUDENTS];
    int count = 0;
    char line[256];

    char myId[32];
    char myName[128];

    /* 1. 학번과 이름 입력 (표준 입력) */
    /* 예: 20231234 홍길동 */
    if (scanf("%31s %127s", myId, myName) != 2) {
        return 0;  /* 입력 실패 시 그냥 종료 */
    }

    /* 2. CSV 파일 열기 (students2.csv) */
    fpIn = fopen("students.csv", "r");
    if (fpIn == NULL) {
        return 0;  /* 파일 오픈 실패 시 종료 */
    }

    /* 3. 출력 파일 열기 (Test.txt) */
    fpOut = fopen("Test.txt", "w");
    if (fpOut == NULL) {
        fclose(fpIn);
        return 0;
    }

    /* 4. 첫 줄: 학번과 이름 출력 */
    fprintf(fpOut, "%s : %s\n", myId, myName);

    /* 5. CSV 헤더 한 줄 버리기 */
    if (fgets(line, sizeof(line), fpIn) == NULL) {
        /* 헤더도 못 읽으면 비정상 CSV */
        fclose(fpIn);
        fclose(fpOut);
        return 0;
    }

    /* 6. CSV 내용 읽기 */
    while (fgets(line, sizeof(line), fpIn) != NULL) {
        Student st;
        char* pNewLine;

        /* 줄 끝의 개행 문자 제거 (있다면) */
        pNewLine = strchr(line, '\n');
        if (pNewLine) *pNewLine = '\0';

        /* 빈 줄 처리 */
        if (line[0] == '\0') {
            continue;
        }

        /* name,atk,def,HP,MP 형식으로 파싱 */
        if (sscanf(line, "%[^,],%d,%d,%d,%d",
            st.name, &st.atk, &st.def, &st.hp, &st.mp) == 5) {
            if (count < MAX_STUDENTS) {
                students[count++] = st;
            }
        }
    }

    fclose(fpIn);

    /* 최소 인원 체크 (문제 조건상 충분히 많다고 가정하지만 안전하게) */
    if (count < 11) {
        fclose(fpOut);
        return 0;
    }

    /* 7. 두 번째 줄: 7번째, 8번째 사람 이름 */
    /* 인덱스: 0-based → 6, 7 */
    fprintf(fpOut, "%s %s\n", students[6].name, students[7].name);

    /* Mother와 Horo의 인덱스 찾기 */
    int i;
    int idxMother = -1;
    int idxHoro = -1;
    for (i = 0; i < count; ++i) {
        if (strcmp(students[i].name, "Mother") == 0) {
            idxMother = i;
        }
        if (strcmp(students[i].name, "Horo") == 0) {
            idxHoro = i;
        }
    }

    /* 혹시 못 찾았을 경우를 대비해 검사 */
    if (idxMother == -1 || idxHoro == -1) {
        /* 문제상 항상 존재한다고 가정하므로,
           여기 오면 그냥 종료 */
        fclose(fpOut);
        return 0;
    }

    /* 8. 세 번째 줄: Mother vs Horo 전투 결과 */
    {
        int result = battle(&students[idxMother], &students[idxHoro]);
        if (result > 0) {
            /* Mother 승리 */
            fprintf(fpOut, "Mother 승! , Horo 패\n");
        }
        else if (result < 0) {
            /* Horo 승리 */
            fprintf(fpOut, "Horo 승! , Mother 패\n");
        }
        else {
            /* 무승부 */
            fprintf(fpOut, "무승부\n");
        }
    }

    /* 9. 네 번째 줄: Mother를 이길 수 있는 사람들 */
    {
        int foundWinner = 0;
        for (i = 0; i < count; ++i) {
            int result;

            /* Mother 자신은 제외 */
            if (strcmp(students[i].name, "Mother") == 0) {
                continue;
            }

            result = battle(&students[i], &students[idxMother]);
            if (result > 0) {  /* i가 Mother를 이김 */
                if (foundWinner) {
                    fprintf(fpOut, ", ");
                }
                fprintf(fpOut, "%s", students[i].name);
                foundWinner = 1;
            }
        }

        if (!foundWinner) {
            /* 아무도 Mother를 못 이김 */
            fprintf(fpOut, "Mother 승!\n");
        }
        else {
            fprintf(fpOut, " 승!\n");
        }
    }

    /* 10. 다섯 번째 줄: 9, 10, 11번째 사람 이름을 이어서 출력 */
    /* 인덱스: 8, 9, 10 */
    fprintf(fpOut, "%s%s%s\n",
        students[8].name,
        students[9].name,
        students[10].name);

    /* 11. 여섯/일곱 번째 줄: 평균 atk, 평균 def */
    {
        long sumAtk = 0;
        long sumDef = 0;
        for (i = 0; i < count; ++i) {
            sumAtk += students[i].atk;
            sumDef += students[i].def;
        }

        /* 정수 나눗셈으로 평균 (소수점 버림) */
        if (count > 0) {
            int avgAtk = (int)(sumAtk / count);
            int avgDef = (int)(sumDef / count);

            fprintf(fpOut, "Average atk: %d\n", avgAtk);
            fprintf(fpOut, "Average def: %d\n", avgDef);
        }
        else {
            fprintf(fpOut, "Average atk: 0\n");
            fprintf(fpOut, "Average def: 0\n");
        }
    }

    /* 12. 마지막 줄: 고정 문장 출력 */
    fprintf(fpOut, "교수님 시험문제 너무 쉽습니다. 담주에 더 어렵게 내주세요");

    fclose(fpOut);
    return 0;
}
