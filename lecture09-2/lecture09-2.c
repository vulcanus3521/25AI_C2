#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char input[100];
    fgets(input, sizeof(input), stdin);

    // 간단한 하이라이트: 'o'를 '*'로 모두 바꾸기(파괴적)
    char buf[128];
    strcpy(buf, input);
    for (char* q = strchr(buf, "fuck"); q != NULL; q = strchr(q + 1, "fuck"))
    {
        *q = '*';
        *(q+1) = '*';
        *(q+2) = '*';
        *(q+3) = '*';
    }
    printf("replace 'fuck'->'****': \"%s\"\n", buf);

    return 0;
}
