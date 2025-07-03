#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX_EXPR 1000
#define STACK_SIZE 100

// ------------------ 스택 구조체 정의 ------------------
typedef struct {
    char data[STACK_SIZE];
    int top;
} CharStack;

typedef struct {
    double data[STACK_SIZE];
    int top;
} DoubleStack;

// ------------------ 연산자 우선순위 ------------------
int precedence(char op) {
    switch (op) {
    case '(': return 0;
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    case '^': return 3;
    }
    return -1;
}

// ------------------ 중위 -> 후위 변환 ------------------
void infixToPostfix(const char* infix, char* postfix) {
    CharStack s;
    s.top = -1;
    int i = 0, j = 0;
    char token;
    char numBuffer[100];

    while (infix[i] != '\0') {
        if (isspace(infix[i])) {
            i++;
            continue;
        }

        // 숫자 또는 음수 처리
        if (isdigit(infix[i]) ||
            ((infix[i] == '-' || infix[i] == '+') && (i == 0 || infix[i - 1] == '(' || infix[i - 1] == '*' || infix[i - 1] == '/' || infix[i - 1] == '+' || infix[i - 1] == '-'))) {
            int k = 0;
            numBuffer[k++] = infix[i++];
            while (isdigit(infix[i]) || infix[i] == '.') {
                numBuffer[k++] = infix[i++];
            }
            numBuffer[k] = '\0';
            for (int m = 0; numBuffer[m] != '\0'; m++) postfix[j++] = numBuffer[m];
            postfix[j++] = ' ';
            continue;
        }

        token = infix[i];
        switch (token) {
        case '(': s.data[++(s.top)] = token; break;
        case ')':
            while (s.top != -1 && s.data[s.top] != '(') {
                postfix[j++] = s.data[(s.top)--];
                postfix[j++] = ' ';
            }
            if (s.top == -1) {
                printf("오류: 괄호 불일치\n"); exit(1);
            }
            s.top--; // '(' 제거
            break;
        case '+': case '-': case '*': case '/': case '^':
            while (s.top != -1 && precedence(s.data[s.top]) >= precedence(token)) {
                postfix[j++] = s.data[(s.top)--];
                postfix[j++] = ' ';
            }
            s.data[++(s.top)] = token;
            break;
        default:
            printf("오류: 잘못된 문자: %c\n", token);
            exit(1);
        }
        i++;
    }
    while (s.top != -1) {
        postfix[j++] = s.data[(s.top)--];
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';
}

// ------------------ 후위 계산 ------------------
double evaluatePostfix(const char* postfix) {
    DoubleStack s;
    s.top = -1;
    char token[100];
    int i = 0;

    while (postfix[i] != '\0') {
        if (isspace(postfix[i])) { i++; continue; }

        if (isdigit(postfix[i]) || ((postfix[i] == '-' || postfix[i] == '+') && isdigit(postfix[i + 1]))) {
            int k = 0;
            token[k++] = postfix[i++];
            while (postfix[i] && !isspace(postfix[i])) {
                token[k++] = postfix[i++];
            }
            token[k] = '\0';
            double val = atof(token);
            s.data[++(s.top)] = val;
        }
        else {
            if (s.top < 1) {
                printf("오류: 피연산자가 부족합니다.\n");
                exit(1);
            }
            double b = s.data[(s.top)--];
            double a = s.data[(s.top)--];
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
    if (s.top != 0) {
        printf("오류: 잘못된 수식입니다.\n");
        exit(1);
    }
    return s.data[(s.top)--];
}

// ------------------ 메인 ------------------
int main() {
    char infix[MAX_EXPR];
    char postfix[MAX_EXPR];

    printf("수식을 입력하세요 (예: (3.5+4.2)*2 ) : ");
    fgets(infix, MAX_EXPR, stdin);
    infix[strcspn(infix, "\n")] = '\0';

    infixToPostfix(infix, postfix);
    printf("후위표기식: %s\n", postfix);

    double result = evaluatePostfix(postfix);
    printf("계산 결과: %.2lf\n", result);

    return 0;
}
