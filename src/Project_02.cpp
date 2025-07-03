/*
  프로그램 개요:
  이 프로그램은 간단한 Undo/Redo 메모장 프로그램입니다.
  사용자는 "add" 명령어로 메모를 추가하고, "undo" 명령어로 마지막 추가를 취소하며,
  "redo" 명령어로 취소된 메모를 다시 실행할 수 있습니다.
  "view" 명령어를 사용하여 현재까지 저장된 메모 내용을 확인할 수 있으며,
  "exit" 명령어를 사용하여 프로그램을 종료합니다.

  주요 기능:
  - add [문자열]: 메모에 새로운 내용을 추가합니다.
  - undo: 마지막 추가된 메모 내용을 취소하고 redo 스택에 저장합니다.
  - redo: 취소된 메모 내용을 다시 실행하여 메모에 복원합니다.
  - view: 현재 저장된 메모 내용을 모두 출력합니다.
  - exit: 프로그램을 종료합니다.

  내부 구조:
  - 두 개의 스택(undo_stack, redo_stack)을 사용하여 Undo/Redo 기능을 구현합니다.
  - undo_stack은 현재 메모에 저장된 내용을 관리하며, redo_stack은 Undo된 내용을 임시로 보관합니다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 100  // 스택에 저장할 최대 항목 수
#define MAX_STR 100    // 저장할 문자열의 최대 길이

// 스택 구조체 정의: 문자열 배열을 이용하여 데이터를 저장
typedef struct {
    char data[MAX_STACK][MAX_STR];  // 문자열들을 저장할 배열
    int top;                        // 현재 스택의 top 인덱스
} Stack;

// 스택 초기화: 스택을 빈 상태로 만들기 위해 top을 -1로 초기화
void initStack(Stack* s) {
    s->top = -1;
}

// 스택이 비어있는지 확인: top이 -1이면 스택이 비어있으므로 1 반환, 아니면 0 반환
int isEmpty(Stack* s) {
    return s->top == -1;
}

// 스택이 가득 찼는지 확인: top이 MAX_STACK - 1이면 스택이 가득 찬 것이므로 1 반환, 아니면 0 반환
int isFull(Stack* s) {
    return s->top == MAX_STACK - 1;
}

// 문자열을 스택에 push: 스택이 가득 차지 않았다면 문자열을 추가
void push(Stack* s, const char* str) {
    if (isFull(s)) {
        printf("스택이 가득 찼습니다!\n");
        return;
    }
    s->top++;                        // top 인덱스를 증가시킨 후
    strcpy(s->data[s->top], str);    // 새 위치에 문자열 복사
}

// 문자열을 스택에서 pop: 스택이 비어 있지 않다면 top 위치의 문자열을 반환하고 top 감소
char* pop(Stack* s) {
    if (isEmpty(s)) {
        return NULL;
    }
    return s->data[s->top--];        // 현재 top의 문자열을 반환 후 top 감소
}

// 스택의 현재 내용을 전체 출력: 저장된 문자열들을 순서대로 출력
void printStack(Stack* s) {
    if (isEmpty(s)) {
        printf("현재 작성된 내용이 없습니다.\n");
        return;
    }
    printf("==== 현재 내용 ====\n");
    for (int i = 0; i <= s->top; i++) {
        printf("%s", s->data[i]);
    }
    printf("===================\n");
}

// 메인 함수: 사용자 명령어에 따라 스택 작업(add, undo, redo, view, exit)을 수행
int main() {
    // Undo와 Redo를 위한 두 개의 스택 선언 및 초기화
    Stack undo_stack, redo_stack;
    initStack(&undo_stack);
    initStack(&redo_stack);

    char input[200];  // 사용자 입력을 저장할 버퍼

    // 프로그램 설명 출력
    printf("간단한 Undo/Redo 메모장 (명령어: add, undo, redo, view, exit)\n");

    while (1) {
        printf("명령어 입력: ");
        fgets(input, sizeof(input), stdin);  // 사용자로부터 한 줄 입력 받음

        // "add" 명령어 처리: "add " 뒤에 오는 문자열을 undo_stack에 추가하고 redo_stack 초기화
        if (strncmp(input, "add ", 4) == 0) {
            char* text = input + 4;  // "add " 이후의 문자열 포인터
            push(&undo_stack, text);
            // 새로운 명령이 추가되면 이전 redo 기록은 무효화됨
            initStack(&redo_stack);
        }
        // "undo" 명령어 처리: undo_stack에서 최근 추가된 문자열을 pop하여 redo_stack에 저장
        else if (strncmp(input, "undo", 4) == 0) {
            char* undone = pop(&undo_stack);
            if (undone) {
                push(&redo_stack, undone);
                printf("Undo: %s", undone);
            }
            else {
                printf("되돌릴 내용이 없습니다.\n");
            }
        }
        // "redo" 명령어 처리: redo_stack에서 최근 제거된 문자열을 pop하여 다시 undo_stack에 추가
        else if (strncmp(input, "redo", 4) == 0) {
            char* redone = pop(&redo_stack);
            if (redone) {
                push(&undo_stack, redone);
                printf("Redo: %s", redone);
            }
            else {
                printf("다시 실행할 내용이 없습니다.\n");
            }
        }
        // "view" 명령어 처리: 현재 undo_stack에 저장된 모든 문자열을 출력
        else if (strncmp(input, "view", 4) == 0) {
            printStack(&undo_stack);
        }
        // "exit" 명령어 처리: 프로그램 종료
        else if (strncmp(input, "exit", 4) == 0) {
            printf("프로그램 종료\n");
            break;
        }
        // 잘못된 명령어 처리: 허용된 명령어가 아닐 경우 알림
        else {
            printf("잘못된 명령입니다. (add, undo, redo, view, exit)\n");
        }
    }

    return 0;
}
