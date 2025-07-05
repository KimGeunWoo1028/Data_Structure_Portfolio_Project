/*
  ���α׷� ����:
  �� ���α׷��� ������ Undo/Redo �޸��� ���α׷��Դϴ�.
  ����ڴ� "add" ��ɾ�� �޸� �߰��ϰ�, "undo" ��ɾ�� ������ �߰��� ����ϸ�,
  "redo" ��ɾ�� ��ҵ� �޸� �ٽ� ������ �� �ֽ��ϴ�.
  "view" ��ɾ ����Ͽ� ������� ����� �޸� ������ Ȯ���� �� ������,
  "exit" ��ɾ ����Ͽ� ���α׷��� �����մϴ�.

  �ֿ� ���:
  - add [���ڿ�]: �޸� ���ο� ������ �߰��մϴ�.
  - undo: ������ �߰��� �޸� ������ ����ϰ� redo ���ÿ� �����մϴ�.
  - redo: ��ҵ� �޸� ������ �ٽ� �����Ͽ� �޸� �����մϴ�.
  - view: ���� ����� �޸� ������ ��� ����մϴ�.
  - exit: ���α׷��� �����մϴ�.

  ���� ����:
  - �� ���� ����(undo_stack, redo_stack)�� ����Ͽ� Undo/Redo ����� �����մϴ�.
  - undo_stack�� ���� �޸� ����� ������ �����ϸ�, redo_stack�� Undo�� ������ �ӽ÷� �����մϴ�.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 100  // ���ÿ� ������ �ִ� �׸� ��
#define MAX_STR 100    // ������ ���ڿ��� �ִ� ����

// ���� ����ü ����: ���ڿ� �迭�� �̿��Ͽ� �����͸� ����
typedef struct {
    char data[MAX_STACK][MAX_STR];  // ���ڿ����� ������ �迭
    int top;                        // ���� ������ top �ε���
} Stack;

// ���� �ʱ�ȭ: ������ �� ���·� ����� ���� top�� -1�� �ʱ�ȭ
void initStack(Stack* s) {
    s->top = -1;
}

// ������ ����ִ��� Ȯ��: top�� -1�̸� ������ ��������Ƿ� 1 ��ȯ, �ƴϸ� 0 ��ȯ
int isEmpty(Stack* s) {
    return s->top == -1;
}

// ������ ���� á���� Ȯ��: top�� MAX_STACK - 1�̸� ������ ���� �� ���̹Ƿ� 1 ��ȯ, �ƴϸ� 0 ��ȯ
int isFull(Stack* s) {
    return s->top == MAX_STACK - 1;
}

// ���ڿ��� ���ÿ� push: ������ ���� ���� �ʾҴٸ� ���ڿ��� �߰�
void push(Stack* s, const char* str) {
    if (isFull(s)) {
        printf("������ ���� á���ϴ�!\n");
        return;
    }
    s->top++;                        // top �ε����� ������Ų ��
    strcpy(s->data[s->top], str);    // �� ��ġ�� ���ڿ� ����
}

// ���ڿ��� ���ÿ��� pop: ������ ��� ���� �ʴٸ� top ��ġ�� ���ڿ��� ��ȯ�ϰ� top ����
char* pop(Stack* s) {
    if (isEmpty(s)) {
        return NULL;
    }
    return s->data[s->top--];        // ���� top�� ���ڿ��� ��ȯ �� top ����
}

// ������ ���� ������ ��ü ���: ����� ���ڿ����� ������� ���
void printStack(Stack* s) {
    if (isEmpty(s)) {
        printf("���� �ۼ��� ������ �����ϴ�.\n");
        return;
    }
    printf("==== ���� ���� ====\n");
    for (int i = 0; i <= s->top; i++) {
        printf("%s", s->data[i]);
    }
    printf("===================\n");
}

// ���� �Լ�: ����� ��ɾ ���� ���� �۾�(add, undo, redo, view, exit)�� ����
int main() {
    // Undo�� Redo�� ���� �� ���� ���� ���� �� �ʱ�ȭ
    Stack undo_stack, redo_stack;
    initStack(&undo_stack);
    initStack(&redo_stack);

    char input[200];  // ����� �Է��� ������ ����

    // ���α׷� ���� ���
    printf("������ Undo/Redo �޸��� (��ɾ�: add, undo, redo, view, exit)\n");

    while (1) {
        printf("��ɾ� �Է�: ");
        fgets(input, sizeof(input), stdin);  // ����ڷκ��� �� �� �Է� ����

        // "add" ��ɾ� ó��: "add " �ڿ� ���� ���ڿ��� undo_stack�� �߰��ϰ� redo_stack �ʱ�ȭ
        if (strncmp(input, "add ", 4) == 0) {
            char* text = input + 4;  // "add " ������ ���ڿ� ������
            push(&undo_stack, text);
            // ���ο� ����� �߰��Ǹ� ���� redo ����� ��ȿȭ��
            initStack(&redo_stack);
        }
        // "undo" ��ɾ� ó��: undo_stack���� �ֱ� �߰��� ���ڿ��� pop�Ͽ� redo_stack�� ����
        else if (strncmp(input, "undo", 4) == 0) {
            char* undone = pop(&undo_stack);
            if (undone) {
                push(&redo_stack, undone);
                printf("Undo: %s", undone);
            }
            else {
                printf("�ǵ��� ������ �����ϴ�.\n");
            }
        }
        // "redo" ��ɾ� ó��: redo_stack���� �ֱ� ���ŵ� ���ڿ��� pop�Ͽ� �ٽ� undo_stack�� �߰�
        else if (strncmp(input, "redo", 4) == 0) {
            char* redone = pop(&redo_stack);
            if (redone) {
                push(&undo_stack, redone);
                printf("Redo: %s", redone);
            }
            else {
                printf("�ٽ� ������ ������ �����ϴ�.\n");
            }
        }
        // "view" ��ɾ� ó��: ���� undo_stack�� ����� ��� ���ڿ��� ���
        else if (strncmp(input, "view", 4) == 0) {
            printStack(&undo_stack);
        }
        // "exit" ��ɾ� ó��: ���α׷� ����
        else if (strncmp(input, "exit", 4) == 0) {
            printf("���α׷� ����\n");
            break;
        }
        // �߸��� ��ɾ� ó��: ���� ��ɾ �ƴ� ��� �˸�
        else {
            printf("�߸��� ����Դϴ�. (add, undo, redo, view, exit)\n");
        }
    }

    return 0;
}
