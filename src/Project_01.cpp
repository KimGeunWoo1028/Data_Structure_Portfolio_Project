/*
  프로그램 개요:
  이 프로그램은 사용자가 입력한 수식을 중위 표기법(infix notation)에서 후위 표기법(postfix notation)으로 변환한 후,
  변환된 후위 표기식을 계산하여 결과를 출력하는 계산기 프로그램입니다.
  덧셈(+), 뺄셈(-), 곱셈(*), 나눗셈(/), 거듭제곱(^) 연산자를 지원하며,
  괄호와 실수 및 음수 표현도 처리할 수 있습니다.

  주요 기능:
  1. infixToPostfix 함수:
     - 중위 수식을 읽어 연산자 우선순위를 고려하여 후위 수식으로 변환.
     - 연산자 우선순위는 괄호 < 덧셈/뺄셈 < 곱셈/나눗셈 < 거듭제곱 순서.
     - 스택(CharStack)을 사용해 연산자 저장 및 처리.
     - 숫자(실수, 음수)와 연산자를 구분해 후위 수식 문자열을 만듦.
  2. evaluatePostfix 함수:
     - 후위 수식을 읽어 피연산자와 연산자를 처리.
     - 피연산자는 DoubleStack 스택에 저장.
     - 연산자가 나오면 스택에서 피연산자 두 개를 꺼내 연산 후 결과를 다시 스택에 저장.
     - 계산 종료 시 최종 결과를 반환.
  3. main 함수:
     - 사용자로부터 중위 수식을 입력받고,
     - 변환 및 계산 결과를 출력.

  내부 구조:
  - 두 개의 스택(CharStack, DoubleStack)을 활용해 변환과 계산 작업을 수행.
  - 오류 처리: 괄호 불일치, 피연산자 부족, 0으로 나누기, 알 수 없는 연산자 등 예외 상황 검사.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX_EXPR 1000
#define STACK_SIZE 100

// ------------------ 스택 구조체 정의 ------------------
// 연산자용 문자 스택 구조체
typedef struct {
    char data[STACK_SIZE]; // 스택 저장 공간
    int top;               // 스택 최상단 인덱스 (-1은 빈 상태)
} CharStack;

// 피연산자용 실수 스택 구조체
typedef struct {
    double data[STACK_SIZE]; // 스택 저장 공간
    int top;                 // 스택 최상단 인덱스 (-1은 빈 상태)
} DoubleStack;

// ------------------ 연산자 우선순위 ------------------
// 연산자 우선순위를 숫자로 반환하는 함수
// 숫자가 클수록 우선순위가 높음
int precedence(char op) {
    switch (op) {
    case '(': return 0;                  // 괄호는 가장 낮은 우선순위
    case '+': case '-': return 1;       // 덧셈, 뺄셈
    case '*': case '/': return 2;       // 곱셈, 나눗셈
    case '^': return 3;                 // 거듭제곱 (최고 우선순위)
    }
    return -1; // 알 수 없는 연산자는 우선순위 없음
}

// ------------------ 중위 -> 후위 변환 ------------------
void infixToPostfix(const char* infix, char* postfix) {
    CharStack s;
    s.top = -1;           // 스택 초기화 (빈 상태)
    int i = 0, j = 0;     // i: 입력 문자열 인덱스, j: 출력 postfix 인덱스
    char token;
    char numBuffer[100];  // 숫자(실수 및 음수) 임시 저장 버퍼

    while (infix[i] != '\0') {
        if (isspace(infix[i])) { // 공백 문자 무시
            i++;
            continue;
        }

        // 숫자 또는 음수/양수 기호가 포함된 숫자 처리
        // 음수/양수 기호는 수식의 시작이거나, 여는 괄호 또는 연산자 뒤에 위치해야 함
        if (isdigit(infix[i]) ||
            ((infix[i] == '-' || infix[i] == '+') &&
                (i == 0 || infix[i - 1] == '(' || infix[i - 1] == '*' ||
                    infix[i - 1] == '/' || infix[i - 1] == '+' || infix[i - 1] == '-'))) {
            int k = 0;
            numBuffer[k++] = infix[i++]; // 부호 혹은 숫자 저장
            while (isdigit(infix[i]) || infix[i] == '.') { // 정수 또는 소수 부분 수집
                numBuffer[k++] = infix[i++];
            }
            numBuffer[k] = '\0'; // 문자열 종료
            // numBuffer에 저장된 숫자 문자열을 postfix에 복사
            for (int m = 0; numBuffer[m] != '\0'; m++) postfix[j++] = numBuffer[m];
            postfix[j++] = ' '; // 숫자와 연산자를 구분하기 위한 공백 추가
            continue;
        }

        token = infix[i];
        switch (token) {
        case '(':
            s.data[++(s.top)] = token; // 여는 괄호는 스택에 무조건 push
            break;
        case ')':
            // 닫는 괄호를 만나면 여는 괄호까지 스택에서 연산자를 모두 꺼내 postfix에 추가
            while (s.top != -1 && s.data[s.top] != '(') {
                postfix[j++] = s.data[(s.top)--];
                postfix[j++] = ' ';
            }
            if (s.top == -1) {
                printf("오류: 괄호 불일치\n");
                exit(1);
            }
            s.top--; // 여는 괄호 제거
            break;
        case '+': case '-': case '*': case '/': case '^':
            // 현재 연산자의 우선순위가 스택 최상단 연산자보다 낮거나 같으면 스택에서 꺼내 postfix에 추가
            while (s.top != -1 && precedence(s.data[s.top]) >= precedence(token)) {
                postfix[j++] = s.data[(s.top)--];
                postfix[j++] = ' ';
            }
            s.data[++(s.top)] = token; // 현재 연산자 스택에 push
            break;
        default:
            printf("오류: 잘못된 문자: %c\n", token);
            exit(1);
        }
        i++;
    }

    // 수식이 끝나면 스택에 남은 모든 연산자를 postfix에 추가
    while (s.top != -1) {
        postfix[j++] = s.data[(s.top)--];
        postfix[j++] = ' ';
    }
    postfix[j] = '\0'; // 문자열 종료
}

// ------------------ 후위 계산 ------------------
double evaluatePostfix(const char* postfix) {
    DoubleStack s;
    s.top = -1;  // 스택 초기화
    char token[100]; // 피연산자 문자열 임시 저장용
    int i = 0;

    while (postfix[i] != '\0') {
        if (isspace(postfix[i])) { // 공백 무시
            i++;
            continue;
        }

        // 숫자(실수, 음수) 처리
        if (isdigit(postfix[i]) || ((postfix[i] == '-' || postfix[i] == '+') && isdigit(postfix[i + 1]))) {
            int k = 0;
            token[k++] = postfix[i++];
            while (postfix[i] && !isspace(postfix[i])) {
                token[k++] = postfix[i++];
            }
            token[k] = '\0';
            double val = atof(token); // 문자열을 double로 변환
            s.data[++(s.top)] = val;  // 스택에 push
        }
        else {
            // 연산자 처리: 스택에서 두 피연산자 pop 후 연산, 결과 다시 push
            if (s.top < 1) {
                printf("오류: 피연산자가 부족합니다.\n");
                exit(1);
            }
            double b = s.data[(s.top)--]; // 두 번째 피연산자
            double a = s.data[(s.top)--]; // 첫 번째 피연산자
            double result;

            switch (postfix[i]) {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/':
                if (b == 0) {
                    printf("0으로 나눌 수 없습니다.\n");
                    exit(1);
                }
                result = a / b; break;
            case '^': result = pow(a, b); break;
            default:
                printf("알 수 없는 연산자: %c\n", postfix[i]);
                exit(1);
            }
            s.data[++(s.top)] = result;
            i++;
        }
    }

    // 연산 완료 후 스택에 결과가 하나만 남아 있어야 정상
    if (s.top != 0) {
        printf("오류: 잘못된 수식입니다.\n");
        exit(1);
    }

    return s.data[(s.top)--]; // 최종 결과 반환
}

// ------------------ 메인 ------------------
int main() {
    char infix[MAX_EXPR];   // 사용자 입력 중위 수식 저장 배열
    char postfix[MAX_EXPR]; // 변환된 후위 수식 저장 배열

    printf("수식을 입력하세요 (예: (3.5+4.2)*2 ) : ");
    fgets(infix, MAX_EXPR, stdin);             // 한 줄 입력 받기
    infix[strcspn(infix, "\n")] = '\0';        // 입력 끝의 개행 문자 제거

    infixToPostfix(infix, postfix);             // 중위 -> 후위 변환 수행
    printf("후위표기식: %s\n", postfix);        // 변환 결과 출력

    double result = evaluatePostfix(postfix);   // 후위 수식 계산
    printf("계산 결과: %.2lf\n", result);       // 계산 결과 출력

    return 0;
}
