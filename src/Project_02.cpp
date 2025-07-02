/*
================================================================================
���α׷���: ���� ���� �ùķ�����
����: �� ���α׷��� ���� ť�� ����Ͽ� ���� ���� �ùķ��̼��� �����մϴ�.
      ������ ������ �ð� �������� �����ϸ�, �� ���� ���� �ð�(���� �ð�)�� �����ϴ�.
      ������ ť�� �� �� ������� ó���Ǹ�, 60�� ���� �ùķ��̼��� ����˴ϴ�.
================================================================================
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>      // �Է� �� ��� ���� �Լ� ����
#include <stdlib.h>     // rand, srand, malloc �� �޸� ���� �Լ� ����
#include <time.h>       // �ð� ���� �Լ� ���� (time �Լ�)
#include <windows.h>    // Sleep �Լ� ����� ���� (�����쿡�� 1�� ��� ȿ��)

// ť�� ������ �ִ� �� �� ����
#define MAX_QUEUE_SIZE 10 // ���� ť�� �ִ� ũ��

// �� ����ü: ���� ��ȣ�� ���� �ð��� ����
typedef struct {
    int id;          // �� ��ȣ
    int serviceTime; // �� ���� �ð� (��)
} Customer;

// ���� ť ����ü: �� �����͸� �����ϴ� �迭�� ť ���� ������
typedef struct {
    Customer data[MAX_QUEUE_SIZE]; // �� �����͸� ������ �迭
    int front;                     // ť ���� �ε���
    int rear;                      // ť ���� �ε���
    int count;                     // ť�� ����� �� ��
} Queue;

// ť �ʱ�ȭ �Լ�: front, rear, count�� 0���� �ʱ�ȭ
void initQueue(Queue* q) {
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

// ť�� ����ִ��� Ȯ���ϴ� �Լ�: count�� 0�̸� �������
int isEmpty(Queue* q) {
    return q->count == 0;
}

// ť�� ���� á���� Ȯ���ϴ� �Լ�: count�� MAX_QUEUE_SIZE�� ������ ���� ��
int isFull(Queue* q) {
    return q->count == MAX_QUEUE_SIZE;
}

// ť�� ���� �߰��ϴ� �Լ�
// ť�� ���� �� ���, �� �߰� �Ұ� �޽����� ����ϰ� �Լ� ����
void enqueue(Queue* q, Customer item) {
    if (isFull(q)) {
        printf("[ ť�� ���� á���ϴ�! �� %d�� ��⿭�� �� ���ϴ�. ]\n", item.id);
        return;
    }
    q->data[q->rear] = item;                        // rear ��ġ�� �� �߰�
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;         // �������� rear �ε��� ������Ʈ
    q->count++;                                     // ť�� �� �� 1 ����
    printf("[ �� %d ��⿭�� �߰� (�����ð�: %d��) ]\n", item.id, item.serviceTime);
}

// ť���� ���� ������ �Լ�
// ť�� ������� �⺻��(-1)�� ���� Customer ��ȯ
Customer dequeue(Queue* q) {
    Customer item = { -1, -1 }; // �⺻�� ����
    if (isEmpty(q)) {
        return item;
    }
    item = q->data[q->front];                       // front ��ġ�� �� �����͸� ������
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;       // �������� front �ε��� ������Ʈ
    q->count--;                                     // ť�� �� �� 1 ����
    return item;
}

// �� ó�� �ùķ��̼� �Լ�
// �� ���� ���� �ð��� ī��Ʈ�ٿ��ϸ� ó���ϴ� ���� �ùķ��̼�
void processCustomer(Customer c) {
    printf("���� ó���� ��: ��#%d\n", c.id);
    // ���� �ð��� 0���� ī��Ʈ�ٿ� �ϸ� 1�� ���
    for (int i = c.serviceTime; i >= 0; i--) {
        printf("%d ", i);
        fflush(stdout);       // ��� ���۸� ��� ����ϱ� ���� ���
        Sleep(1000);          // 1�� ��� (1000 �и���)
    }
    printf("\n<�� %d ó�� �Ϸ�: %d��>\n\n", c.id, c.serviceTime);
}

int main() {
    // �ùķ��̼ǿ� ����� ť �ʱ�ȭ
    Queue q;
    initQueue(&q);

    // ���� �õ� �ʱ�ȭ (���� �ð� ���)
    srand((unsigned int)time(NULL));

    int currentTime = 0;                     // �ùķ��̼� ���� �ð� (0�ʺ��� ����)
    int nextArrival = rand() % 5 + 3;          // ù �� ���� �ð�: 3~7�� ���� ����
    int customerID = 1;                      // �� ID ���� ��ȣ

    // �ùķ��̼� ���� �޽��� ���
    printf("=== ���� ���� �ùķ����� ���� ===\n");

    // 60�� �ùķ��̼� ����
    while (1) {
        printf("���� �ð�: %d��\n", currentTime);

        // �� ���� ���� Ȯ��: ���� �ð��� ���� ���� �ð��� ��ġ�ϸ� �� �� ����
        if (currentTime == nextArrival) {
            Customer newCustomer;
            newCustomer.id = customerID++;          // �� ��ȣ ���� �� ����
            newCustomer.serviceTime = rand() % 11 + 5; // ���� �ð�: 5~15�� ����

            // �� �� ���� �޽��� ���
            printf("[ ���� �� ���� : ��#%d, �����ð� %d�� ]\n", newCustomer.id, newCustomer.serviceTime);
            enqueue(&q, newCustomer);                // ť�� �� �� �߰�

            // ���� �� ���� �ð� �缳�� (���� �ð� + 3~7�� ����)
            nextArrival = currentTime + (rand() % 5 + 3);
        }

        // ť�� ��� ���� ���� ������, ���� ������ ���� ó�� ����
        if (!isEmpty(&q)) {
            Customer current = dequeue(&q);
            processCustomer(current);
        }
        else {
            // ť�� ������� "�����" �޽��� ��� �� 1�� ���
            printf("ó���� �� ����. 1�� ��� ��...\n\n");
            Sleep(1000);
        }

        currentTime++;  // ���� �ð� 1�� ����

        // 60�� �ùķ��̼� ����
        if (currentTime > 60) break;
    }

    // �ùķ��̼� ���� �޽��� ���
    printf("=== �ùķ��̼� ���� ===\n");
    return 0;
}
