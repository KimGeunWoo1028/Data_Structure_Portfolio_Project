/*
  ���α׷�: MP3 ��� �ùķ����� (���� 2�� ���)
  ����: ����ڰ� ���� ����ϰ�, ����/���� ������ �̵��ϴ� ��� ����
  Ư¡: �� ���� ������ ����Ͽ� ���� ��/���� �� �̵��� ȿ�������� ó��
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define TITLE_LEN 100

// ���ڿ��� �����ϴ� ���� ����ü ����
typedef struct {
    char data[MAX][TITLE_LEN];  // �� ���� ���� �迭 (2����)
    int top;
} Stack;

// ���� �Լ���
void initStack(Stack* s) {
    s->top = -1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

int isFull(Stack* s) {
    return s->top == MAX - 1;
}

void push(Stack* s, const char* str) {
    if (isFull(s)) {
        printf("������ ���� á���ϴ�!\n");
        return;
    }
    strcpy(s->data[++(s->top)], str);
}

char* pop(Stack* s) {
    if (isEmpty(s)) {
        return NULL;
    }
    return s->data[(s->top)--];
}

char* peek(Stack* s) {
    if (isEmpty(s)) {
        return NULL;
    }
    return s->data[s->top];
}

void printStack(Stack* s, const char* name) {
    printf("== %s ��� (top �� bottom) ==\n", name);
    if (isEmpty(s)) {
        printf("(��� ����)\n");
        return;
    }
    for (int i = s->top; i >= 0; i--) {
        printf("%d: %s\n", s->top - i + 1, s->data[i]);
    }
}

int main() {
    Stack prevStack, nextStack;
    initStack(&prevStack);
    initStack(&nextStack);

    char currentSong[TITLE_LEN] = "";  // ���� ��� ���� �� (�ʱⰪ ����)
    char command[20], input[TITLE_LEN];

    printf("MP3 ��� �ùķ����� ����\n");
    printf("��ɾ�: play [���], prev, next, exit\n\n");

    while (1) {
        printf("\n���� ��: %s\n", strlen(currentSong) > 0 ? currentSong : "(��� ���� �� ����)");
        printf(">> ");
        scanf("%s", command);

        if (strcmp(command, "play") == 0) {
            scanf(" %[^\n]", input);  // ���� ������ �� ���� �Է�
            if (strlen(currentSong) > 0) {
                // ���� ���� �ִٸ� ���� �� ���ÿ� push
                push(&prevStack, currentSong);
            }
            // �� ���� ���� ������ ����
            strcpy(currentSong, input);

            // ���� �� ������ �ʱ�ȭ (�� ���� Ʋ�� ������ ��� ���� �ʱ�ȭ)
            initStack(&nextStack);

            printf("���: %s\n", currentSong);
        }
        else if (strcmp(command, "prev") == 0) {
            if (isEmpty(&prevStack)) {
                printf("���� ���� �����ϴ�.\n");
            }
            else {
                // ���� ���� next ���ÿ� push
                push(&nextStack, currentSong);
                // prev ���ÿ��� ���� �� pop
                strcpy(currentSong, pop(&prevStack));
                printf("���� �� ���: %s\n", currentSong);
            }
        }
        else if (strcmp(command, "next") == 0) {
            if (isEmpty(&nextStack)) {
                printf("���� ���� �����ϴ�.\n");
            }
            else {
                // ���� ���� prev ���ÿ� push
                push(&prevStack, currentSong);
                // next ���ÿ��� ���� �� pop
                strcpy(currentSong, pop(&nextStack));
                printf("���� �� ���: %s\n", currentSong);
            }
        }
        else if (strcmp(command, "list") == 0) {
            printStack(&prevStack, "���� �� ����");
            printStack(&nextStack, "���� �� ����");
        }
        else if (strcmp(command, "exit") == 0) {
            printf("���α׷��� �����մϴ�.\n");
            break;
        }
        else {
            printf("�� �� ���� ����Դϴ�.\n");
        }
    }

    return 0;
}
