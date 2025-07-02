/*
  ���α׷�: MP3 ��� �ùķ����� (���� 2�� ���)
  ����: ����ڰ� ���� ����ϰ�, ����/���� ������ �̵��ϴ� ��� ����
  Ư¡: �� ���� ������ ����Ͽ� ���� ��/���� �� �̵��� ȿ�������� ó��
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100          // ���� �ִ� ũ��
#define TITLE_LEN 100    // �� ���� �ִ� ����

// ���ڿ��� �����ϴ� ���� ����ü ����
typedef struct {
    char data[MAX][TITLE_LEN];  // �� ���� ���� �迭 (2����)
    int top;                    // ������ ���� top �ε���
} Stack;

// ���� �ʱ�ȭ �Լ�: top�� -1�� ������ �� ���·� ����
void initStack(Stack* s) {
    s->top = -1;
}

// ������ ������� Ȯ���ϴ� �Լ� (��������� 1 ��ȯ)
int isEmpty(Stack* s) {
    return s->top == -1;
}

// ������ ���� á���� Ȯ���ϴ� �Լ� (���� á���� 1 ��ȯ)
int isFull(Stack* s) {
    return s->top == MAX - 1;
}

// ���ÿ� ���ڿ�(push) �߰��ϴ� �Լ�
void push(Stack* s, const char* str) {
    if (isFull(s)) {                    // ���� á���� ��� ��� �� �Լ� ����
        printf("������ ���� á���ϴ�!\n");
        return;
    }
    strcpy(s->data[++(s->top)], str);  // top ���� �� �ش� ��ġ�� ���ڿ� ����
}

// ���ÿ��� ���ڿ�(pop) ������ �Լ�
char* pop(Stack* s) {
    if (isEmpty(s)) {                   // ������� NULL ��ȯ
        return NULL;
    }
    return s->data[(s->top)--];        // ���� top ��ġ ���ڿ� ��ȯ �� top ����
}

// ������ ���� �� ���ڿ��� Ȯ���ϴ� �Լ� (pop���� �ʰ� ��ȯ)
char* peek(Stack* s) {
    if (isEmpty(s)) {                   // ������� NULL ��ȯ
        return NULL;
    }
    return s->data[s->top];             // top ��ġ ���ڿ� ��ȯ
}

// ���� ���� ���� ��� �Լ�
// name: ���� �̸� (��: "���� �� ����", "���� �� ����")
void printStack(Stack* s, const char* name) {
    printf("\n-- %s ��� (�ֽ� �� ����) --\n", name);
    if (isEmpty(s)) {                   // ��������� �޽��� ���
        printf("   (��� ����)\n");
        return;
    }
    // top�������� 0���� ����Ͽ� �ֽ� �׸���� ������ �׸� ������ ǥ��
    for (int i = s->top; i >= 0; i--) {
        printf("   -> %s\n", s->data[i]);
    }
}

// ����ڿ��� ��ɾ� �ȳ��� ����ϴ� �Լ�
void printHelp() {
    printf("\n��ɾ� �ȳ�:\n");
    printf("  play [���]  - �� �� ���\n");
    printf("  prev         - ���� �� ���\n");
    printf("  next         - ���� �� ���\n");
    printf("  list         - ����/���� �� ��� ����\n");
    printf("  exit         - ���α׷� ����\n");
    printf("------------------------------\n");
}

int main() {
    Stack prevStack, nextStack;         // ���� �� ���ð� ���� �� ���� ����
    initStack(&prevStack);              // ���� �� ���� �ʱ�ȭ
    initStack(&nextStack);              // ���� �� ���� �ʱ�ȭ

    char currentSong[TITLE_LEN] = "";  // ���� ��� ���� �� (�ʱⰪ�� ����)
    char command[20], input[TITLE_LEN];// ����� ��ɾ�� �Է� ��� �����

    printf("MP3 ��� �ùķ����� ����\n");
    printHelp();                       // ���α׷� ���� �� ��ɾ� �ȳ� ���

    // ���� ������ ���� ����� �Է� ó��
    while (1) {
        // ���� ��� ���� �� ��� (������ ���� ǥ��)
        printf("\n���� ��: %s\n", strlen(currentSong) > 0 ? currentSong : "(����)");
        printf("��ɾ� �Է� >> ");
        scanf("%s", command);           // ��ɾ� �Է� �ޱ�

        // play ��ɾ� ó��: ���ο� �� ���
        if (strcmp(command, "play") == 0) {
            scanf(" %[^\n]", input);    // ���� ���� ��� �Է� �ޱ�
            if (strlen(currentSong) > 0) {
                // ���� ���� ������ ���� �� ���ÿ� ����
                push(&prevStack, currentSong);
            }
            // �� ���� ���� ������ ����
            strcpy(currentSong, input);

            // ���� �� ������ �ʱ�ȭ (�� �� ��� �� ������ ��� ���� ��� ����)
            initStack(&nextStack);

            printf("��� ����: %s\n", currentSong);
        }
        // prev ��ɾ� ó��: ���� ������ �̵�
        else if (strcmp(command, "prev") == 0) {
            if (isEmpty(&prevStack)) {
                // ���� �� ������ ��������� �ȳ� �޽��� ���
                printf("���� ���� �����ϴ�.\n");
            }
            else {
                // ���� ���� ���� �� ���ÿ� ����
                push(&nextStack, currentSong);
                // ���� �� ���ÿ��� �� ���� ���� ������ ����
                strcpy(currentSong, pop(&prevStack));
                printf("���� �� ���: %s\n", currentSong);
            }
        }
        // next ��ɾ� ó��: ���� ������ �̵�
        else if (strcmp(command, "next") == 0) {
            if (isEmpty(&nextStack)) {
                // ���� �� ������ ��������� �ȳ� �޽��� ���
                printf("���� ���� �����ϴ�.\n");
            }
            else {
                // ���� ���� ���� �� ���ÿ� ����
                push(&prevStack, currentSong);
                // ���� �� ���ÿ��� �� ���� ���� ������ ����
                strcpy(currentSong, pop(&nextStack));
                printf("���� �� ���: %s\n", currentSong);
            }
        }
        // list ��ɾ� ó��: ����/���� �� ��� ���
        else if (strcmp(command, "list") == 0) {
            printStack(&prevStack, "���� �� ����");
            printStack(&nextStack, "���� �� ����");
        }
        // exit ��ɾ� ó��: ���α׷� ����
        else if (strcmp(command, "exit") == 0) {
            printf("���α׷��� �����մϴ�.\n");
            break;
        }
        // �� �� ���� ��ɾ� ó��
        else {
            printf("�� �� ���� ����Դϴ�. �ٽ� �õ��ϼ���.\n");
            printHelp();  // �𸣴� ��ɾ��� �� ��ɾ� �ȳ� �ٽ� ���
        }
    }

    return 0;
}
