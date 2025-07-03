/*
  ���α׷� ����:
  �� ���α׷��� ����ڰ� �Է��� DNA ���⼭���� �ùٸ� ��������� �����Ǿ� �ִ��� �˻��մϴ�.

  �˻� ��Ģ:
  - DNA ������� ������ ���� ��Ȯ�ϰ� ��Ī�Ǿ�� �մϴ�:
    A�� T��, T�� A��, G�� C��, C�� G�� ¦�� �̷�ϴ�.

  �۵� ���:
  - �Է¹��� DNA ���ڿ��� �� ������ ���ÿ� �����մϴ�.
  - �� ������ �� ����� ���ÿ��� ���� ���⸦ �ϳ��� ���Ͽ� �ùٸ� ¦���� Ȯ���մϴ�.

  Ư¡:
  - ������� �ùٸ��� ���� ��� ��� ��ġ���� ������ �߻��ߴ����� ��� ����(1���� ����)���� ����մϴ�.
  - ��ü ���� ��� ������ ���� �޽����� ����մϴ�.

  ����:
  - �Էµ� DNA ���⼭�� ���̴� ¦������ �մϴ�.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// ���� ����ü ����: ���� �迭�� top ������ ����
typedef struct {
    char data[MAX];  // ���ÿ� ������ ���� ���� �迭
    int top;         // ���� top ��ġ (���� �ֱٿ� push�� ����� �ε���)
} Stack;

// ���� �ʱ�ȭ �Լ�: top�� -1�� ����
void initStack(Stack* s) {
    s->top = -1;
}

// ������ ������� Ȯ��
int isEmpty(Stack* s) {
    return s->top == -1;
}

// ������ ���� á���� Ȯ��
int isFull(Stack* s) {
    return s->top == MAX - 1;
}

// ���ÿ� ���� �ϳ� push
void push(Stack* s, char c) {
    if (isFull(s)) {
        printf("���� �����÷ο� �߻�!\n");
        exit(1);
    }
    s->data[++(s->top)] = c;
}

// ���ÿ��� ���� �ϳ� pop
char pop(Stack* s) {
    if (isEmpty(s)) {
        printf("���� ����÷ο� �߻�!\n");
        exit(1);
    }
    return s->data[(s->top)--];
}

// �� ���ڰ� DNA ����� �������� Ȯ���ϴ� �Լ�
int isPair(char a, char b) {
    return (a == 'A' && b == 'T') ||
        (a == 'T' && b == 'A') ||
        (a == 'G' && b == 'C') ||
        (a == 'C' && b == 'G');
}

int main() {
    Stack stack;             // ���� ����
    initStack(&stack);       // ���� �ʱ�ȭ

    char dna[MAX];           // DNA ���⼭�� ���ڿ� ���� �迭

    // ����ڷκ��� ���⼭�� �Է� �ޱ�
    printf("DNA ���⼭�� �Է� (��: ATGCAT): ");
    scanf("%s", dna);

    int len = strlen(dna);   // �Էµ� ���ڿ� ���� ���

    // DNA ���̴� ¦������ ���� �̷� �� ����
    if (len % 2 != 0) {
        printf("���⼭�� ���̰� Ȧ���Դϴ�. ���� �������� �ʽ��ϴ�.\n");
        return 1;
    }

    int half = len / 2;  // ���ڿ��� ������ ����

    // �� ������ ���ÿ� push
    for (int i = 0; i < half; i++) {
        push(&stack, dna[i]);
    }

    // �� ������ �� ���ݰ� ��
    int valid = 1; // �⺻���� ���� ��� �´� ������ ����

    for (int i = half; i < len; i++) {
        char fromStack = pop(&stack);  // ���ÿ��� �� ���� ����
        char current = dna[i];         // ���� �˻��� ����

        if (!isPair(fromStack, current)) {
            // ¦�� ���� �ʴ� ���: ���� �޽��� ���
            // �� ���� ���ڴ� ���ڿ����� i��° ��ġ�� �����Ƿ�
            // ��� �������δ� (i+1)��° ������
            printf("¦�� ���� �ʽ��ϴ�: %c - %c (DNA ���ڿ��� %d��° ����)\n",
                fromStack, current, i + 1);
            valid = 0;
            break;
        }
    }

    // ��� ���� �´� ���
    if (valid) {
        printf("��� ������� ��Ȯ�� �½��ϴ�!\n");
    }

    return 0;
}
