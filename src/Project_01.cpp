#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ������ �ִ� ũ��� ���ڿ� ���� ������ ����
#define MAX_STACK 100     // ���� �ִ� ���� ��
#define MAX_STR 100       // �� ���ڿ��� �ִ� ����

// ���� ����ü ����
typedef struct {
    char data[MAX_STACK][MAX_STR];  // ���ÿ� ����� ���ڿ����� ���� 2���� �迭
    int top;                        // ������ �ֻ��� �ε����� ��Ÿ��, �ʱⰪ -1�� ������ ��� ������ �ǹ�
} Stack;

// ���� �ʱ�ȭ �Լ�
// �Ű�����: Stack ����ü ������
// ����: ������ top�� -1�� �����Ͽ� ������ ����ִ� ���·� �ʱ�ȭ
void initStack(Stack* s) {
    s->top = -1;
}

// ������ ������� Ȯ���ϴ� �Լ�
// �Ű�����: Stack ����ü ������
// ��ȯ��: ������ ��������� 1(true), �ƴϸ� 0(false)
int isEmpty(Stack* s) {
    return s->top == -1;
}

// ������ ���� á���� Ȯ���ϴ� �Լ�
// �Ű�����: Stack ����ü ������
// ��ȯ��: ������ ���� á���� 1(true), �ƴϸ� 0(false)
int isFull(Stack* s) {
    return s->top == MAX_STACK - 1;
}

// ���ڿ��� ���ÿ� �߰��ϴ� push �Լ�
// �Ű�����: Stack ����ü ������, �߰��� ���ڿ�(const char *str)
// ����: 
// 1. ������ ���� á���� Ȯ��, ���� �������� ���� �޽��� ���
// 2. ���ÿ� ���ڿ��� �����ϰ�, top ���� ������Ŵ
void push(Stack* s, const char* str) {
    if (isFull(s)) {
        printf("������ ���� á���ϴ�!\n");
        return;
    }
    s->top++;
    strcpy(s->data[s->top], str);  // ���ڿ� �����Ͽ� ���ÿ� ����
}

// ���ÿ��� ������ �׸��� ������ pop �Լ�
// �Ű�����: Stack ����ü ������
// ��ȯ��: ���ÿ��� ���� ���ڿ� (���ڿ� ������), ������ ��������� NULL ��ȯ
char* pop(Stack* s) {
    if (isEmpty(s)) {
        return NULL;
    }
    return s->data[s->top--];   // ���� top�� ��ġ�� ���ڿ� ��ȯ �� top ����
}

// ������ ���� ������ ��� ����ϴ� �Լ�
// �Ű�����: Stack ����ü ������
// ����: 
// 1. ������ ��������� �ȳ� �޽��� ���
// 2. ���ÿ� ����� ��� ���ڿ����� ������� ���
void printStack(Stack* s) {
    if (isEmpty(s)) {
        printf("���� �ۼ��� ������ �����ϴ�.\n");
        return;
    }
    printf("==== ���� ���� ====\n");
    for (int i = 0; i <= s->top; i++) {
        printf("%s", s->data[i]);  // �� ���ڿ� ��� (�ٹٲ��� ���Ե� ��� �״�� ��µ�)
    }
    printf("===================\n");
}

// ���� �Լ�: ������ Undo/Redo �޸��� ���α׷�
int main() {
    // undo �� redo ���� ���� �� �ʱ�ȭ
    Stack undo_stack, redo_stack;
    initStack(&undo_stack);  // undo ���� �ʱ�ȭ
    initStack(&redo_stack);  // redo ���� �ʱ�ȭ

    char input[200];  // ����� �Է��� ���� ����

    // ���α׷� ���� �ȳ� �޽��� ���
    printf("������ Undo/Redo �޸��� (��ɾ�: add, undo, redo, view, exit)\n");

    // ���� ������ ���� ����� ��ɾ� ó��
    while (1) {
        printf("��ɾ� �Է�: ");
        // ����� �Է� �ޱ� (���� ���� ����)
        fgets(input, sizeof(input), stdin);

        // "add " ��ɾ� ó��: �޸� ������ �߰�
        if (strncmp(input, "add ", 4) == 0) {
            char* text = input + 4;   // "add " ������ ���ڿ��� ����
            push(&undo_stack, text);  // undo ���ÿ� ���� �߰�
            initStack(&redo_stack);   // ���ο� ���� �߰� �� redo ���� �ʱ�ȭ
        }
        // "undo" ��ɾ� ó��: ������ �߰��� ������ �ǵ���
        else if (strncmp(input, "undo", 4) == 0) {
            char* undone = pop(&undo_stack);   // undo ���ÿ��� ������ ���� ������
            if (undone) {
                push(&redo_stack, undone);     // redo ���ÿ� ����Ͽ� redo �����ϰ� ��
                printf("Undo: %s", undone);      // �ǵ����� ���� ���
            }
            else {
                printf("�ǵ��� ������ �����ϴ�.\n");
            }
        }
        // "redo" ��ɾ� ó��: �ǵ��� ������ �ٽ� ����
        else if (strncmp(input, "redo", 4) == 0) {
            char* redone = pop(&redo_stack);     // redo ���ÿ��� ������ ���� ������
            if (redone) {
                push(&undo_stack, redone);       // undo ���ÿ� �ٽ� �߰�
                printf("Redo: %s", redone);        // �ٽ� ����� ���� ���
            }
            else {
                printf("�ٽ� ������ ������ �����ϴ�.\n");
            }
        }
        // "view" ��ɾ� ó��: ���� undo ������ ��� ������ ���
        else if (strncmp(input, "view", 4) == 0) {
            printStack(&undo_stack);
        }
        // "exit" ��ɾ� ó��: ���α׷� ����
        else if (strncmp(input, "exit", 4) == 0) {
            printf("���α׷� ����\n");
            break;  // ���� ���� Ż��
        }
        // �ùٸ��� ���� ��ɾ� ó��
        else {
            printf("�߸��� ����Դϴ�. (add, undo, redo, view, exit)\n");
        }
    }

    return 0;  // ���α׷� ���� ����
}
