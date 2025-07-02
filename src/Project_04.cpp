/*
  프로그램: MP3 재생 시뮬레이터 (스택 2개 사용)
  목적: 사용자가 곡을 재생하고, 이전/다음 곡으로 이동하는 기능 구현
  특징: 두 개의 스택을 사용하여 이전 곡/다음 곡 이동을 효율적으로 처리
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100          // 스택 최대 크기
#define TITLE_LEN 100    // 곡 제목 최대 길이

// 문자열을 저장하는 스택 구조체 정의
typedef struct {
    char data[MAX][TITLE_LEN];  // 곡 제목 저장 배열 (2차원)
    int top;                    // 스택의 현재 top 인덱스
} Stack;

// 스택 초기화 함수: top을 -1로 설정해 빈 상태로 만듦
void initStack(Stack* s) {
    s->top = -1;
}

// 스택이 비었는지 확인하는 함수 (비어있으면 1 반환)
int isEmpty(Stack* s) {
    return s->top == -1;
}

// 스택이 가득 찼는지 확인하는 함수 (가득 찼으면 1 반환)
int isFull(Stack* s) {
    return s->top == MAX - 1;
}

// 스택에 문자열(push) 추가하는 함수
void push(Stack* s, const char* str) {
    if (isFull(s)) {                    // 가득 찼으면 경고 출력 후 함수 종료
        printf("스택이 가득 찼습니다!\n");
        return;
    }
    strcpy(s->data[++(s->top)], str);  // top 증가 후 해당 위치에 문자열 복사
}

// 스택에서 문자열(pop) 꺼내는 함수
char* pop(Stack* s) {
    if (isEmpty(s)) {                   // 비었으면 NULL 반환
        return NULL;
    }
    return s->data[(s->top)--];        // 현재 top 위치 문자열 반환 후 top 감소
}

// 스택의 가장 위 문자열을 확인하는 함수 (pop하지 않고 반환)
char* peek(Stack* s) {
    if (isEmpty(s)) {                   // 비었으면 NULL 반환
        return NULL;
    }
    return s->data[s->top];             // top 위치 문자열 반환
}

// 스택 내부 상태 출력 함수
// name: 스택 이름 (예: "이전 곡 스택", "다음 곡 스택")
void printStack(Stack* s, const char* name) {
    printf("\n-- %s 목록 (최신 → 과거) --\n", name);
    if (isEmpty(s)) {                   // 비어있으면 메시지 출력
        printf("   (비어 있음)\n");
        return;
    }
    // top에서부터 0까지 출력하여 최신 항목부터 오래된 항목 순서로 표시
    for (int i = s->top; i >= 0; i--) {
        printf("   -> %s\n", s->data[i]);
    }
}

// 사용자에게 명령어 안내를 출력하는 함수
void printHelp() {
    printf("\n명령어 안내:\n");
    printf("  play [곡명]  - 새 곡 재생\n");
    printf("  prev         - 이전 곡 재생\n");
    printf("  next         - 다음 곡 재생\n");
    printf("  list         - 이전/다음 곡 목록 보기\n");
    printf("  exit         - 프로그램 종료\n");
    printf("------------------------------\n");
}

int main() {
    Stack prevStack, nextStack;         // 이전 곡 스택과 다음 곡 스택 선언
    initStack(&prevStack);              // 이전 곡 스택 초기화
    initStack(&nextStack);              // 다음 곡 스택 초기화

    char currentSong[TITLE_LEN] = "";  // 현재 재생 중인 곡 (초기값은 없음)
    char command[20], input[TITLE_LEN];// 사용자 명령어와 입력 곡명 저장용

    printf("MP3 재생 시뮬레이터 시작\n");
    printHelp();                       // 프로그램 시작 시 명령어 안내 출력

    // 무한 루프를 돌며 사용자 입력 처리
    while (1) {
        // 현재 재생 중인 곡 출력 (없으면 별도 표시)
        printf("\n현재 곡: %s\n", strlen(currentSong) > 0 ? currentSong : "(없음)");
        printf("명령어 입력 >> ");
        scanf("%s", command);           // 명령어 입력 받기

        // play 명령어 처리: 새로운 곡 재생
        if (strcmp(command, "play") == 0) {
            scanf(" %[^\n]", input);    // 공백 포함 곡명 입력 받기
            if (strlen(currentSong) > 0) {
                // 현재 곡이 있으면 이전 곡 스택에 넣음
                push(&prevStack, currentSong);
            }
            // 새 곡을 현재 곡으로 설정
            strcpy(currentSong, input);

            // 다음 곡 스택은 초기화 (새 곡 재생 시 앞으로 듣던 곡은 모두 삭제)
            initStack(&nextStack);

            printf("재생 시작: %s\n", currentSong);
        }
        // prev 명령어 처리: 이전 곡으로 이동
        else if (strcmp(command, "prev") == 0) {
            if (isEmpty(&prevStack)) {
                // 이전 곡 스택이 비어있으면 안내 메시지 출력
                printf("이전 곡이 없습니다.\n");
            }
            else {
                // 현재 곡을 다음 곡 스택에 저장
                push(&nextStack, currentSong);
                // 이전 곡 스택에서 곡 꺼내 현재 곡으로 설정
                strcpy(currentSong, pop(&prevStack));
                printf("이전 곡 재생: %s\n", currentSong);
            }
        }
        // next 명령어 처리: 다음 곡으로 이동
        else if (strcmp(command, "next") == 0) {
            if (isEmpty(&nextStack)) {
                // 다음 곡 스택이 비어있으면 안내 메시지 출력
                printf("다음 곡이 없습니다.\n");
            }
            else {
                // 현재 곡을 이전 곡 스택에 저장
                push(&prevStack, currentSong);
                // 다음 곡 스택에서 곡 꺼내 현재 곡으로 설정
                strcpy(currentSong, pop(&nextStack));
                printf("다음 곡 재생: %s\n", currentSong);
            }
        }
        // list 명령어 처리: 이전/다음 곡 목록 출력
        else if (strcmp(command, "list") == 0) {
            printStack(&prevStack, "이전 곡 스택");
            printStack(&nextStack, "다음 곡 스택");
        }
        // exit 명령어 처리: 프로그램 종료
        else if (strcmp(command, "exit") == 0) {
            printf("프로그램을 종료합니다.\n");
            break;
        }
        // 알 수 없는 명령어 처리
        else {
            printf("알 수 없는 명령입니다. 다시 시도하세요.\n");
            printHelp();  // 모르는 명령어일 때 명령어 안내 다시 출력
        }
    }

    return 0;
}
