/*
  ���α׷���: ������ �� ä�ù� �޽��� ���� �ùķ�����
  ����:
    - ä�� �޽����� ť(FIFO ����)�� ����
    - ť�� �ִ� �뷮�� �ʰ��ϸ� ���� ������ �޽����� �ڵ� ����
    - ����� ��ɿ� ���� �޽����� �߰�, ����, ��ü ���
  Ư¡:
    - ���� ť ���� ��� (������ ���� ������ �޸� ����)
    - "send"�� �޽��� �߰�
    - "view"�� ��� �޽��� ���
    - "delete"�� ���� ������ �޽��� ���� ����
    - "exit"���� ����
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MESSAGES 10     // ť�� ���� ������ �ִ� �޽��� ��
#define MAX_LEN 100        // �� �޽����� �ִ� ����

// ť ����ü ����
typedef struct {
    char messages[MAX_MESSAGES][MAX_LEN]; // �޽��� ���� �迭 (2����)
    int front;  // ���� ������ �޽��� ��ġ
    int rear;   // ���� �������� �߰��� �޽��� ��ġ
    int size;   // ���� ť�� ����� �޽��� ��
} MessageQueue;

// ť �ʱ�ȭ �Լ�
void initQueue(MessageQueue* q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

// ť�� ����ִ��� Ȯ��
int isEmpty(MessageQueue* q) {
    return q->size == 0;
}

// ť�� ���� á���� Ȯ��
int isFull(MessageQueue* q) {
    return q->size == MAX_MESSAGES;
}

// ť�� �޽��� �߰� (enqueue)
void enqueue(MessageQueue* q, const char* msg) {
    if (isFull(q)) {
        // ť�� ���� á���� ���� ������ �޽����� ���� ����
        printf("[�ڵ� ����] �޽��� �ʰ��� ������ �޽��� ����: %s\n", q->messages[q->front]);
        q->front = (q->front + 1) % MAX_MESSAGES;
        q->size--;
    }
    // ���ο� �޽��� �߰�
    q->rear = (q->rear + 1) % MAX_MESSAGES;
    strcpy(q->messages[q->rear], msg);
    q->size++;
    printf("[�޽��� �߰�] %s\n", msg);
}

// ť���� �޽��� ���� (dequeue)
void dequeue(MessageQueue* q) {
    if (isEmpty(q)) {
        printf("������ �޽����� �����ϴ�.\n");
        return;
    }
    printf("[�޽��� ����] %s\n", q->messages[q->front]);
    q->front = (q->front + 1) % MAX_MESSAGES;
    q->size--;
}

// ť�� ��� �޽��� ���
void viewMessages(MessageQueue* q) {
    if (isEmpty(q)) {
        printf("[��ȭ ����]\n");
        return;
    }
    printf("\n[ä�� �޽��� ���] (�ֽ� �� �ƴ�)\n");
    for (int i = 0; i < q->size; i++) {
        int index = (q->front + i) % MAX_MESSAGES;
        printf("%d: %s\n", i + 1, q->messages[index]);
    }
}

int main() {
    MessageQueue chatQueue;
    initQueue(&chatQueue);

    char command[10];
    char message[MAX_LEN];

    printf("=== ������ �� ä�ù� �޽��� ���� �ùķ����� ===\n");
    printf("��ɾ� ���: send / view / delete / exit\n");

    while (1) {
        printf("\n> ��ɾ� �Է�: ");
        scanf("%s", command);

        if (strcmp(command, "send") == 0) {
            getchar();  // ���� ���� ����
            printf("���� �޽���: ");
            fgets(message, sizeof(message), stdin);
            message[strcspn(message, "\n")] = '\0'; // ���� ���� ����
            enqueue(&chatQueue, message);
        }
        else if (strcmp(command, "view") == 0) {
            viewMessages(&chatQueue);
        }
        else if (strcmp(command, "delete") == 0) {
            dequeue(&chatQueue);
        }
        else if (strcmp(command, "exit") == 0) {
            printf("���α׷� ����\n");
            break;
        }
        else {
            printf("�߸��� ��ɾ��Դϴ�. �ٽ� �õ��ϼ���.\n");
        }
    }

    return 0;
}