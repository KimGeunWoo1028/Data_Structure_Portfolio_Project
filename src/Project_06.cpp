/*
 * ���α׷���: ������ �� ä�ù� �޽��� ���� �ùķ����� (C���)
 * ����:
 *   - ����ڰ� �Է��� ä�� �޽����� ������� �����ϰ�,
 *   - ���� ����� �޽����� Ȯ���ϰų� ������ �޽����� ������ �� ������,
 *   - '/exit' ��ɾ�� ���α׷��� ������ �� �ִ� �ùķ�����.
 *
 * ���:
 *   - �Ϲ� ���ڿ� �Է� �� �޽����� �����.
 *   - '/view' ���: ����� ��� �޽����� ��ȣ�� �Բ� ���.
 *   - '/delete' ���: ���� �������� ����� �޽����� ����.
 *   - '/exit' ���: ���α׷� ����.
 *
 * Ư¡:
 *   - ����ü�� ����� �޽����� �迭�� �����ϰ�, �޽��� ������ ����.
 *   - �ִ� �޽��� ��(MAX_MSG)�� �޽��� ����(MAX_LEN)�� ����� ����.
 *   - ���� ä�� ������ �ƴ�����, �޽��� ����/������ ���� ������ ������.
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MSG 100     // �ִ� ������ �� �ִ� �޽��� ��
#define MAX_LEN 100     // �� �޽����� �ִ� ����

 // �޽����� �����ϴ� ����ü ����
typedef struct {
    char messages[MAX_MSG][MAX_LEN];  // �޽����� �����ϴ� 2���� �迭
    int count;                        // ���� ����� �޽��� ����
} Chat;

// �޽����� �߰��ϴ� �Լ�
void addMessage(Chat* chat, const char* msg) {
    if (chat->count >= MAX_MSG) {
        // �ִ� ������ �ʰ��� ��� ���� ���
        printf("�޽��� ���� ������ ���� á���ϴ�!\n");
        return;
    }

    // ���ο� �޽����� �迭�� ���� (���� �ʰ� ����)
    strncpy(chat->messages[chat->count], msg, MAX_LEN - 1);
    chat->messages[chat->count][MAX_LEN - 1] = '\0'; // �� ���� ����
    chat->count++; // �޽��� �� ����
}

// ����� ��� �޽����� ����ϴ� �Լ�
void viewMessages(const Chat* chat) {
    if (chat->count == 0) {
        printf("����� �޽����� �����ϴ�.\n");
        return;
    }

    printf("\n[ ��ü �޽��� ��� ]\n");
    for (int i = 0; i < chat->count; i++) {
        printf("%2d: %s\n", i + 1, chat->messages[i]);  // 1������ ���
    }
    printf("----------------------\n");
}

// ������ �޽����� �����ϴ� �Լ�
void deleteLastMessage(Chat* chat) {
    if (chat->count == 0) {
        // ������ �޽����� ���� ���
        printf("������ �޽����� �����ϴ�.\n");
        return;
    }

    // ���� �ֱ� �޽����� ����� �� ����
    printf("������ �޽���: %s\n", chat->messages[chat->count - 1]);
    chat->count--; // �޽��� �� ����
}

// ���� �Լ�
int main() {
    Chat chat;           // �޽��� ����� ����ü ���� ����
    chat.count = 0;      // �޽��� �� �ʱ�ȭ

    char input[MAX_LEN]; // ����� �Է� ����� ���ڿ� �迭

    // ���α׷� ���� �޽��� �� ��ɾ� �ȳ�
    printf("=== ������ �� ä�ù� �޽��� �ùķ����� ===\n");
    printf("��ɾ�:\n");
    printf("  �޽��� �Է�: �Ϲ� ���ڿ�\n");
    printf("  /view       : ��ü �޽��� ����\n");
    printf("  /delete     : ������ �޽��� ����\n");
    printf("  /exit       : ���α׷� ����\n");

    // ���� ����: ����� �Է��� ����ؼ� ����
    while (1) {
        printf("\n�Է� >> ");
        fgets(input, sizeof(input), stdin); // �Է� �ޱ� (���� ����)

        // �Է� ���� ���� ����('\n') ����
        input[strcspn(input, "\n")] = '\0';

        // �Է��� '/exit'�̸� ����
        if (strcmp(input, "/exit") == 0) {
            printf("ä�� ����.\n");
            break;
        }
        // �Է��� '/view'�̸� ��ü �޽��� ���
        else if (strcmp(input, "/view") == 0) {
            viewMessages(&chat);
        }
        // �Է��� '/delete'�̸� ������ �޽��� ����
        else if (strcmp(input, "/delete") == 0) {
            deleteLastMessage(&chat);
        }
        // �Ϲ� ���ڿ� �Է��̸� �޽��� ����
        else if (strlen(input) > 0) {
            addMessage(&chat, input);
            printf("�޽��� ���� �Ϸ�.\n");
        }
        // �� ���ڿ� �Է� ó��
        else {
            printf("�� �Է��� ������� �ʽ��ϴ�.\n");
        }
    }

    return 0; // ���α׷� ����
}