/*
  프로그램: MP3 재생 시뮬레이터 (스택 2개 사용)
  목적: 사용자가 곡을 재생하고, 이전/다음 곡으로 이동하는 기능 구현
  특징: 두 개의 스택을 사용하여 이전 곡/다음 곡 이동을 효율적으로 처리
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define TITLE_LEN 100

// 문자열을 저장하는 스택 구조체 정의
typedef struct {
    char data[MAX][TITLE_LEN];  // 곡 제목 저장 배열 (2차원)
    int top;
} Stack;

// 스택 함수들
void initStack(Stack* s) {
    s->top = -1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

int isFull(Stack* s) {
    return s->top == MAX - 1;
}

void push(Stack* s, const char* str) {
    if (isFull(s)) {
        printf("스택이 가득 찼습니다!\n");
        return;
    }
    strcpy(s->data[++(s->top)], str);
}

char* pop(Stack* s) {
    if (isEmpty(s)) {
        return NULL;
    }
    return s->data[(s->top)--];
}

char* peek(Stack* s) {
    if (isEmpty(s)) {
        return NULL;
    }
    return s->data[s->top];
}

void printStack(Stack* s, const char* name) {
    printf("== %s 목록 (top → bottom) ==\n", name);
    if (isEmpty(s)) {
        printf("(비어 있음)\n");
        return;
    }
    for (int i = s->top; i >= 0; i--) {
        printf("%d: %s\n", s->top - i + 1, s->data[i]);
    }
}

int main() {
    Stack prevStack, nextStack;
    initStack(&prevStack);
    initStack(&nextStack);

    char currentSong[TITLE_LEN] = "";  // 현재 재생 중인 곡 (초기값 없음)
    char command[20], input[TITLE_LEN];

    printf("MP3 재생 시뮬레이터 시작\n");
    printf("명령어: play [곡명], prev, next, exit\n\n");

    while (1) {
        printf("\n현재 곡: %s\n", strlen(currentSong) > 0 ? currentSong : "(재생 중인 곡 없음)");
        printf(">> ");
        scanf("%s", command);

        if (strcmp(command, "play") == 0) {
            scanf(" %[^\n]", input);  // 공백 포함한 곡 제목 입력
            if (strlen(currentSong) > 0) {
                // 현재 곡이 있다면 이전 곡 스택에 push
                push(&prevStack, currentSong);
            }
            // 새 곡을 현재 곡으로 설정
            strcpy(currentSong, input);

            // 다음 곡 스택은 초기화 (새 곡을 틀면 앞으로 듣던 곡은 초기화)
            initStack(&nextStack);

            printf("재생: %s\n", currentSong);
        }
        else if (strcmp(command, "prev") == 0) {
            if (isEmpty(&prevStack)) {
                printf("이전 곡이 없습니다.\n");
            }
            else {
                // 현재 곡을 next 스택에 push
                push(&nextStack, currentSong);
                // prev 스택에서 이전 곡 pop
                strcpy(currentSong, pop(&prevStack));
                printf("이전 곡 재생: %s\n", currentSong);
            }
        }
        else if (strcmp(command, "next") == 0) {
            if (isEmpty(&nextStack)) {
                printf("다음 곡이 없습니다.\n");
            }
            else {
                // 현재 곡을 prev 스택에 push
                push(&prevStack, currentSong);
                // next 스택에서 다음 곡 pop
                strcpy(currentSong, pop(&nextStack));
                printf("다음 곡 재생: %s\n", currentSong);
            }
        }
        else if (strcmp(command, "list") == 0) {
            printStack(&prevStack, "이전 곡 스택");
            printStack(&nextStack, "다음 곡 스택");
        }
        else if (strcmp(command, "exit") == 0) {
            printf("프로그램을 종료합니다.\n");
            break;
        }
        else {
            printf("알 수 없는 명령입니다.\n");
        }
    }

    return 0;
}
