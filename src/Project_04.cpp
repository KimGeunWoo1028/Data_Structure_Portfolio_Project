/*
  프로그램 개요:
  이 프로그램은 사용자가 입력한 DNA 염기서열이 올바른 염기쌍으로 구성되어 있는지 검사합니다.

  검사 규칙:
  - DNA 염기쌍은 다음과 같이 정확하게 매칭되어야 합니다:
    A는 T와, T는 A와, G는 C와, C는 G와 짝을 이룹니다.

  작동 방식:
  - 입력받은 DNA 문자열의 앞 절반을 스택에 저장합니다.
  - 뒤 절반의 각 염기와 스택에서 꺼낸 염기를 하나씩 비교하여 올바른 짝인지 확인합니다.

  특징:
  - 염기쌍이 올바르지 않은 경우 어느 위치에서 오류가 발생했는지를 사람 기준(1부터 시작)으로 출력합니다.
  - 전체 쌍이 모두 맞으면 성공 메시지를 출력합니다.

  제한:
  - 입력된 DNA 염기서열 길이는 짝수여야 합니다.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// 스택 구조체 정의: 문자 배열과 top 포인터 포함
typedef struct {
    char data[MAX];  // 스택에 저장할 염기 문자 배열
    int top;         // 현재 top 위치 (가장 최근에 push된 요소의 인덱스)
} Stack;

// 스택 초기화 함수: top을 -1로 설정
void initStack(Stack* s) {
    s->top = -1;
}

// 스택이 비었는지 확인
int isEmpty(Stack* s) {
    return s->top == -1;
}

// 스택이 가득 찼는지 확인
int isFull(Stack* s) {
    return s->top == MAX - 1;
}

// 스택에 문자 하나 push
void push(Stack* s, char c) {
    if (isFull(s)) {
        printf("스택 오버플로우 발생!\n");
        exit(1);
    }
    s->data[++(s->top)] = c;
}

// 스택에서 문자 하나 pop
char pop(Stack* s) {
    if (isEmpty(s)) {
        printf("스택 언더플로우 발생!\n");
        exit(1);
    }
    return s->data[(s->top)--];
}

// 두 문자가 DNA 염기쌍 관계인지 확인하는 함수
int isPair(char a, char b) {
    return (a == 'A' && b == 'T') ||
        (a == 'T' && b == 'A') ||
        (a == 'G' && b == 'C') ||
        (a == 'C' && b == 'G');
}

int main() {
    Stack stack;             // 스택 선언
    initStack(&stack);       // 스택 초기화

    char dna[MAX];           // DNA 염기서열 문자열 저장 배열

    // 사용자로부터 염기서열 입력 받기
    printf("DNA 염기서열 입력 (예: ATGCAT): ");
    scanf("%s", dna);

    int len = strlen(dna);   // 입력된 문자열 길이 계산

    // DNA 길이는 짝수여야 쌍을 이룰 수 있음
    if (len % 2 != 0) {
        printf("염기서열 길이가 홀수입니다. 쌍이 완전하지 않습니다.\n");
        return 1;
    }

    int half = len / 2;  // 문자열을 반으로 나눔

    // 앞 절반을 스택에 push
    for (int i = 0; i < half; i++) {
        push(&stack, dna[i]);
    }

    // 뒤 절반을 앞 절반과 비교
    int valid = 1; // 기본값은 쌍이 모두 맞는 것으로 설정

    for (int i = half; i < len; i++) {
        char fromStack = pop(&stack);  // 스택에서 한 글자 꺼냄
        char current = dna[i];         // 현재 검사할 염기

        if (!isPair(fromStack, current)) {
            // 짝이 맞지 않는 경우: 오류 메시지 출력
            // 비교 중인 글자는 문자열에서 i번째 위치에 있으므로
            // 사람 기준으로는 (i+1)번째 글자임
            printf("짝이 맞지 않습니다: %c - %c (DNA 문자열의 %d번째 글자)\n",
                fromStack, current, i + 1);
            valid = 0;
            break;
        }
    }

    // 모든 쌍이 맞는 경우
    if (valid) {
        printf("모든 염기쌍이 정확히 맞습니다!\n");
    }

    return 0;
}
