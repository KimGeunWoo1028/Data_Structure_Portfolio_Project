/*
  ���α׷� ����:
  �� ���α׷��� ����ڰ� �Է��� ������ ���� ǥ���(infix notation)���� ���� ǥ���(postfix notation)���� ��ȯ�� ��,
  ��ȯ�� ���� ǥ����� ����Ͽ� ����� ����ϴ� ���� ���α׷��Դϴ�.
  ����(+), ����(-), ����(*), ������(/), �ŵ�����(^) �����ڸ� �����ϸ�,
  ��ȣ�� �Ǽ� �� ���� ǥ���� ó���� �� �ֽ��ϴ�.

  �ֿ� ���:
  1. infixToPostfix �Լ�:
     - ���� ������ �о� ������ �켱������ ����Ͽ� ���� �������� ��ȯ.
     - ������ �켱������ ��ȣ < ����/���� < ����/������ < �ŵ����� ����.
     - ����(CharStack)�� ����� ������ ���� �� ó��.
     - ����(�Ǽ�, ����)�� �����ڸ� ������ ���� ���� ���ڿ��� ����.
  2. evaluatePostfix �Լ�:
     - ���� ������ �о� �ǿ����ڿ� �����ڸ� ó��.
     - �ǿ����ڴ� DoubleStack ���ÿ� ����.
     - �����ڰ� ������ ���ÿ��� �ǿ����� �� ���� ���� ���� �� ����� �ٽ� ���ÿ� ����.
     - ��� ���� �� ���� ����� ��ȯ.
  3. main �Լ�:
     - ����ڷκ��� ���� ������ �Է¹ް�,
     - ��ȯ �� ��� ����� ���.

  ���� ����:
  - �� ���� ����(CharStack, DoubleStack)�� Ȱ���� ��ȯ�� ��� �۾��� ����.
  - ���� ó��: ��ȣ ����ġ, �ǿ����� ����, 0���� ������, �� �� ���� ������ �� ���� ��Ȳ �˻�.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX_EXPR 1000
#define STACK_SIZE 100

// ------------------ ���� ����ü ���� ------------------
// �����ڿ� ���� ���� ����ü
typedef struct {
    char data[STACK_SIZE]; // ���� ���� ����
    int top;               // ���� �ֻ�� �ε��� (-1�� �� ����)
} CharStack;

// �ǿ����ڿ� �Ǽ� ���� ����ü
typedef struct {
    double data[STACK_SIZE]; // ���� ���� ����
    int top;                 // ���� �ֻ�� �ε��� (-1�� �� ����)
} DoubleStack;

// ------------------ ������ �켱���� ------------------
// ������ �켱������ ���ڷ� ��ȯ�ϴ� �Լ�
// ���ڰ� Ŭ���� �켱������ ����
int precedence(char op) {
    switch (op) {
    case '(': return 0;                  // ��ȣ�� ���� ���� �켱����
    case '+': case '-': return 1;       // ����, ����
    case '*': case '/': return 2;       // ����, ������
    case '^': return 3;                 // �ŵ����� (�ְ� �켱����)
    }
    return -1; // �� �� ���� �����ڴ� �켱���� ����
}

// ------------------ ���� -> ���� ��ȯ ------------------
void infixToPostfix(const char* infix, char* postfix) {
    CharStack s;
    s.top = -1;           // ���� �ʱ�ȭ (�� ����)
    int i = 0, j = 0;     // i: �Է� ���ڿ� �ε���, j: ��� postfix �ε���
    char token;
    char numBuffer[100];  // ����(�Ǽ� �� ����) �ӽ� ���� ����

    while (infix[i] != '\0') {
        if (isspace(infix[i])) { // ���� ���� ����
            i++;
            continue;
        }

        // ���� �Ǵ� ����/��� ��ȣ�� ���Ե� ���� ó��
        // ����/��� ��ȣ�� ������ �����̰ų�, ���� ��ȣ �Ǵ� ������ �ڿ� ��ġ�ؾ� ��
        if (isdigit(infix[i]) ||
            ((infix[i] == '-' || infix[i] == '+') &&
                (i == 0 || infix[i - 1] == '(' || infix[i - 1] == '*' ||
                    infix[i - 1] == '/' || infix[i - 1] == '+' || infix[i - 1] == '-'))) {
            int k = 0;
            numBuffer[k++] = infix[i++]; // ��ȣ Ȥ�� ���� ����
            while (isdigit(infix[i]) || infix[i] == '.') { // ���� �Ǵ� �Ҽ� �κ� ����
                numBuffer[k++] = infix[i++];
            }
            numBuffer[k] = '\0'; // ���ڿ� ����
            // numBuffer�� ����� ���� ���ڿ��� postfix�� ����
            for (int m = 0; numBuffer[m] != '\0'; m++) postfix[j++] = numBuffer[m];
            postfix[j++] = ' '; // ���ڿ� �����ڸ� �����ϱ� ���� ���� �߰�
            continue;
        }

        token = infix[i];
        switch (token) {
        case '(':
            s.data[++(s.top)] = token; // ���� ��ȣ�� ���ÿ� ������ push
            break;
        case ')':
            // �ݴ� ��ȣ�� ������ ���� ��ȣ���� ���ÿ��� �����ڸ� ��� ���� postfix�� �߰�
            while (s.top != -1 && s.data[s.top] != '(') {
                postfix[j++] = s.data[(s.top)--];
                postfix[j++] = ' ';
            }
            if (s.top == -1) {
                printf("����: ��ȣ ����ġ\n");
                exit(1);
            }
            s.top--; // ���� ��ȣ ����
            break;
        case '+': case '-': case '*': case '/': case '^':
            // ���� �������� �켱������ ���� �ֻ�� �����ں��� ���ų� ������ ���ÿ��� ���� postfix�� �߰�
            while (s.top != -1 && precedence(s.data[s.top]) >= precedence(token)) {
                postfix[j++] = s.data[(s.top)--];
                postfix[j++] = ' ';
            }
            s.data[++(s.top)] = token; // ���� ������ ���ÿ� push
            break;
        default:
            printf("����: �߸��� ����: %c\n", token);
            exit(1);
        }
        i++;
    }

    // ������ ������ ���ÿ� ���� ��� �����ڸ� postfix�� �߰�
    while (s.top != -1) {
        postfix[j++] = s.data[(s.top)--];
        postfix[j++] = ' ';
    }
    postfix[j] = '\0'; // ���ڿ� ����
}

// ------------------ ���� ��� ------------------
double evaluatePostfix(const char* postfix) {
    DoubleStack s;
    s.top = -1;  // ���� �ʱ�ȭ
    char token[100]; // �ǿ����� ���ڿ� �ӽ� �����
    int i = 0;

    while (postfix[i] != '\0') {
        if (isspace(postfix[i])) { // ���� ����
            i++;
            continue;
        }

        // ����(�Ǽ�, ����) ó��
        if (isdigit(postfix[i]) || ((postfix[i] == '-' || postfix[i] == '+') && isdigit(postfix[i + 1]))) {
            int k = 0;
            token[k++] = postfix[i++];
            while (postfix[i] && !isspace(postfix[i])) {
                token[k++] = postfix[i++];
            }
            token[k] = '\0';
            double val = atof(token); // ���ڿ��� double�� ��ȯ
            s.data[++(s.top)] = val;  // ���ÿ� push
        }
        else {
            // ������ ó��: ���ÿ��� �� �ǿ����� pop �� ����, ��� �ٽ� push
            if (s.top < 1) {
                printf("����: �ǿ����ڰ� �����մϴ�.\n");
                exit(1);
            }
            double b = s.data[(s.top)--]; // �� ��° �ǿ�����
            double a = s.data[(s.top)--]; // ù ��° �ǿ�����
            double result;

            switch (postfix[i]) {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/':
                if (b == 0) {
                    printf("0���� ���� �� �����ϴ�.\n");
                    exit(1);
                }
                result = a / b; break;
            case '^': result = pow(a, b); break;
            default:
                printf("�� �� ���� ������: %c\n", postfix[i]);
                exit(1);
            }
            s.data[++(s.top)] = result;
            i++;
        }
    }

    // ���� �Ϸ� �� ���ÿ� ����� �ϳ��� ���� �־�� ����
    if (s.top != 0) {
        printf("����: �߸��� �����Դϴ�.\n");
        exit(1);
    }

    return s.data[(s.top)--]; // ���� ��� ��ȯ
}

// ------------------ ���� ------------------
int main() {
    char infix[MAX_EXPR];   // ����� �Է� ���� ���� ���� �迭
    char postfix[MAX_EXPR]; // ��ȯ�� ���� ���� ���� �迭

    printf("������ �Է��ϼ��� (��: (3.5+4.2)*2 ) : ");
    fgets(infix, MAX_EXPR, stdin);             // �� �� �Է� �ޱ�
    infix[strcspn(infix, "\n")] = '\0';        // �Է� ���� ���� ���� ����

    infixToPostfix(infix, postfix);             // ���� -> ���� ��ȯ ����
    printf("����ǥ���: %s\n", postfix);        // ��ȯ ��� ���

    double result = evaluatePostfix(postfix);   // ���� ���� ���
    printf("��� ���: %.2lf\n", result);       // ��� ��� ���

    return 0;
}
