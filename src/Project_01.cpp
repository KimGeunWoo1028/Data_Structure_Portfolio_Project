#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 스택의 최대 크기와 문자열 길이 제한을 정의
#define MAX_STACK 100     // 스택 최대 원소 수
#define MAX_STR 100       // 각 문자열의 최대 길이

// 스택 구조체 정의
typedef struct {
    char data[MAX_STACK][MAX_STR];  // 스택에 저장될 문자열들을 위한 2차원 배열
    int top;                        // 스택의 최상위 인덱스를 나타냄, 초기값 -1은 스택이 비어 있음을 의미
} Stack;

// 스택 초기화 함수
// 매개변수: Stack 구조체 포인터
// 동작: 스택의 top을 -1로 설정하여 스택을 비어있는 상태로 초기화
void initStack(Stack* s) {
    s->top = -1;
}

// 스택이 비었는지 확인하는 함수
// 매개변수: Stack 구조체 포인터
// 반환값: 스택이 비어있으면 1(true), 아니면 0(false)
int isEmpty(Stack* s) {
    return s->top == -1;
}

// 스택이 가득 찼는지 확인하는 함수
// 매개변수: Stack 구조체 포인터
// 반환값: 스택이 가득 찼으면 1(true), 아니면 0(false)
int isFull(Stack* s) {
    return s->top == MAX_STACK - 1;
}

// 문자열을 스택에 추가하는 push 함수
// 매개변수: Stack 구조체 포인터, 추가할 문자열(const char *str)
// 동작: 
// 1. 스택이 가득 찼는지 확인, 가득 차있으면 에러 메시지 출력
// 2. 스택에 문자열을 복사하고, top 값을 증가시킴
void push(Stack* s, const char* str) {
    if (isFull(s)) {
        printf("스택이 가득 찼습니다!\n");
        return;
    }
    s->top++;
    strcpy(s->data[s->top], str);  // 문자열 복사하여 스택에 저장
}

// 스택에서 마지막 항목을 꺼내는 pop 함수
// 매개변수: Stack 구조체 포인터
// 반환값: 스택에서 꺼낸 문자열 (문자열 포인터), 스택이 비어있으면 NULL 반환
char* pop(Stack* s) {
    if (isEmpty(s)) {
        return NULL;
    }
    return s->data[s->top--];   // 현재 top에 위치한 문자열 반환 후 top 감소
}

// 스택의 현재 내용을 모두 출력하는 함수
// 매개변수: Stack 구조체 포인터
// 동작: 
// 1. 스택이 비어있으면 안내 메시지 출력
// 2. 스택에 저장된 모든 문자열들을 순서대로 출력
void printStack(Stack* s) {
    if (isEmpty(s)) {
        printf("현재 작성된 내용이 없습니다.\n");
        return;
    }
    printf("==== 현재 내용 ====\n");
    for (int i = 0; i <= s->top; i++) {
        printf("%s", s->data[i]);  // 각 문자열 출력 (줄바꿈이 포함된 경우 그대로 출력됨)
    }
    printf("===================\n");
}

// 메인 함수: 간단한 Undo/Redo 메모장 프로그램
int main() {
    // undo 및 redo 스택 선언 및 초기화
    Stack undo_stack, redo_stack;
    initStack(&undo_stack);  // undo 스택 초기화
    initStack(&redo_stack);  // redo 스택 초기화

    char input[200];  // 사용자 입력을 위한 버퍼

    // 프로그램 시작 안내 메시지 출력
    printf("간단한 Undo/Redo 메모장 (명령어: add, undo, redo, view, exit)\n");

    // 무한 루프를 돌며 사용자 명령어 처리
    while (1) {
        printf("명령어 입력: ");
        // 사용자 입력 받기 (개행 문자 포함)
        fgets(input, sizeof(input), stdin);

        // "add " 명령어 처리: 메모 내용을 추가
        if (strncmp(input, "add ", 4) == 0) {
            char* text = input + 4;   // "add " 이후의 문자열을 추출
            push(&undo_stack, text);  // undo 스택에 내용 추가
            initStack(&redo_stack);   // 새로운 내용 추가 시 redo 스택 초기화
        }
        // "undo" 명령어 처리: 마지막 추가된 내용을 되돌림
        else if (strncmp(input, "undo", 4) == 0) {
            char* undone = pop(&undo_stack);   // undo 스택에서 마지막 내용 꺼내기
            if (undone) {
                push(&redo_stack, undone);     // redo 스택에 기록하여 redo 가능하게 함
                printf("Undo: %s", undone);      // 되돌려진 내용 출력
            }
            else {
                printf("되돌릴 내용이 없습니다.\n");
            }
        }
        // "redo" 명령어 처리: 되돌린 내용을 다시 실행
        else if (strncmp(input, "redo", 4) == 0) {
            char* redone = pop(&redo_stack);     // redo 스택에서 마지막 내용 꺼내기
            if (redone) {
                push(&undo_stack, redone);       // undo 스택에 다시 추가
                printf("Redo: %s", redone);        // 다시 실행된 내용 출력
            }
            else {
                printf("다시 실행할 내용이 없습니다.\n");
            }
        }
        // "view" 명령어 처리: 현재 undo 스택의 모든 내용을 출력
        else if (strncmp(input, "view", 4) == 0) {
            printStack(&undo_stack);
        }
        // "exit" 명령어 처리: 프로그램 종료
        else if (strncmp(input, "exit", 4) == 0) {
            printf("프로그램 종료\n");
            break;  // 무한 루프 탈출
        }
        // 올바르지 않은 명령어 처리
        else {
            printf("잘못된 명령입니다. (add, undo, redo, view, exit)\n");
        }
    }

    return 0;  // 프로그램 정상 종료
}
