/*
 * ���α׷���: �ܾ� �ڵ��ϼ� �ùķ����� (C���)
 * ����:
 *   ����ڰ� ���� �ϳ��� �Է��ϸ� ���� �Էµ� ���ڿ��� �����ϰ�,
 *   Undo(/u), Redo(/r) ����� �����ϴ� ������ �ڵ��ϼ� �ùķ������Դϴ�.
 *
 *   - �Է� ���ڴ� ���ÿ� �����Ͽ� ���ڿ� ���� ����
 *   - Undo ����� �ֱ� �Է� ���� �ϳ��� �Է� ���ÿ��� ���� Undo ���ÿ� ����
 *   - Redo ����� Undo ���ÿ��� ���ڸ� �ٽ� �Է� ���ÿ� ����
 *   - �Է� ���¸� �������� �̸� ���ǵ� �ܾ� �������� ���� �Է� ���ڿ��� �����ϴ� �ܾ���� ��õ
 *
 * ����:
 *   ���� �� ���ڸ� �Է��ϸ� ���� �Է¿� �߰��ǰ�, ��õ �ܾ ��µ˴ϴ�.
 *   ��ɾ�� '/'�� �����ϸ� ������ �����մϴ�.
 *     /u : Undo (�Է��� ���� �ϳ� �ǵ�����)
 *     /r : Redo (Undo�� ���� �ٽ� �Է��ϱ�)
 *     /q : ����
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_INPUT_SIZE 100    // �ִ� �Է� ���� ��
#define MAX_UNDO_SIZE 100     // Undo ���� �ִ� ũ�� (�Է°� ����)
#define MAX_WORDS 10          // ���� �ܾ� ��
#define MAX_WORD_LEN 20       // �ܾ� �ִ� ����

 // ���� ���� ����ü ����
typedef struct {
    char data[MAX_INPUT_SIZE]; // ���� ���� �迭
    int top;                   // ���� �ֻ�� �ε���
} CharStack;

// ���� �ʱ�ȭ �Լ�: top�� -1�� �����Ͽ� �� ���·� ����
void initStack(CharStack* s) {
    s->top = -1;
}

// ������ ������� Ȯ���ϴ� �Լ�
int isEmpty(CharStack* s) {
    return s->top == -1;
}

// ���ÿ� ���� �ֱ� (push)
// ���� �� 1 ��ȯ, ���� �� 0 ��ȯ (���� ���� á�� ��)
int push(CharStack* s, char ch) {
    if (s->top >= MAX_INPUT_SIZE - 1) return 0; // ������ ���� á��
    s->data[++(s->top)] = ch;
    return 1;
}

// ���ÿ��� ���� ���� (pop)
// ���� �� 1 ��ȯ�ϰ� *ch�� ���� ����, ���� �� 0 ��ȯ (���� ����� ��)
int pop(CharStack* s, char* ch) {
    if (isEmpty(s)) return 0;
    *ch = s->data[(s->top)--];
    return 1;
}

// ���ÿ� ����� ���ڸ� ���ڿ��� ��ȯ�Ͽ� out�� ����
// bottom(0)���� top���� ������� �����ϰ� ���� �ι���('\0') �߰�
void stackToString(CharStack* s, char* out) {
    int i;
    for (i = 0; i <= s->top; i++) {
        out[i] = s->data[i];
    }
    out[i] = '\0';
}

// prefix�� word�� ���λ����� Ȯ���ϴ� �Լ� (��ҹ��� ���� ����)
// prefix�� word ���� �κа� ��ġ�ϸ� 1 ��ȯ, �ƴϸ� 0 ��ȯ
int isPrefix(const char* prefix, const char* word) {
    while (*prefix && *word) {
        if (tolower(*prefix) != tolower(*word)) return 0;
        prefix++;
        word++;
    }
    return *prefix == '\0'; // prefix ���ڿ��� �������� ���λ� ����
}

int main() {
    CharStack inputStack;  // ���� �Է� ���ڿ� ����� ����
    CharStack undoStack;   // Undo�� ���� ����� ���� (Redo��)
    initStack(&inputStack);
    initStack(&undoStack);

    // �ڵ��ϼ� �ĺ� �ܾ� ����Ʈ (����)
    const char* dictionary[MAX_WORDS] = {
        "apple", "banana", "grape", "orange", "melon",
        "apricot", "blueberry", "blackberry", "pear", "peach"
    };

    char command[20];            // ����� �Է� ����
    char currentInput[MAX_INPUT_SIZE]; // ���� �Է� ���ڿ�
    char ch;                    // ���� ����� ����

    // ���α׷� �ȳ� �޽��� ���
    printf("�ڵ��ϼ� �ùķ����� ����\n");
    printf("��ɾ�: ���� �Է� | /u: undo | /r: redo | /q: ����\n");
    printf("��) ���� �Է�: a\n");
    printf("    undo: /u\n");
    printf("    redo: /r\n");
    printf("    ����: /q\n");

    while (1) {
        // ���� �Է� ���ڿ��� ���ÿ��� ���ڿ��� ��ȯ
        stackToString(&inputStack, currentInput);

        // ����ڿ��� ���� ���¿� �Է� ��� ǥ��
        printf("���� �Է�: '%s' > ", currentInput);

        // �Է� �ޱ�
        if (fgets(command, sizeof(command), stdin) == NULL) break;

        // �Է� ���� ���๮�� ����
        size_t len = strlen(command);
        if (len > 0 && command[len - 1] == '\n')
            command[len - 1] = '\0';

        // �� �Է� ó��
        if (strlen(command) == 0) {
            printf("�Է��� ������ϴ�. �ٽ� �Է����ּ���.\n");
            continue;
        }

        if (command[0] == '/') {
            // �����÷� �����ϸ� ��ɾ� ó��
            if (strcmp(command, "/q") == 0) {
                // ���� ���
                printf("�����մϴ�.\n");
                break;
            }
            else if (strcmp(command, "/u") == 0) {
                // Undo ���: �Է� ���ÿ��� ���� �ϳ� ���� undo ���ÿ� ����
                if (pop(&inputStack, &ch)) {
                    push(&undoStack, ch);
                }
                else {
                    printf("Undo �Ұ�: �Էµ� ���ڰ� �����ϴ�.\n");
                }
            }
            else if (strcmp(command, "/r") == 0) {
                // Redo ���: undo ���ÿ��� ���� �ϳ� ���� �Է� ���ÿ� �ٽ� ����
                if (pop(&undoStack, &ch)) {
                    push(&inputStack, ch);
                }
                else {
                    printf("Redo �Ұ�: �ǵ��� ���ڰ� �����ϴ�.\n");
                }
            }
            else {
                // �� �� ���� ��ɾ� ó��
                printf("�� �� ���� ��ɾ��Դϴ�.\n");
            }
        }
        else if (strlen(command) == 1) {
            // ���� �ϳ� �Է¹��� ���
            ch = command[0];
            if (!push(&inputStack, ch)) {
                // ������ �� á�� �� ó��
                printf("�Է� ������ ���� á���ϴ�.\n");
            }
            else {
                // �� ���� �Է� �� redo ���� �ʱ�ȭ
                initStack(&undoStack);
            }
        }
        else {
            // ���̰� 1���� ũ�� ��ɾ �ƴ� �߸��� �Է� ó��
            printf("�߸��� �Է��Դϴ�. ��ɾ�� '/'�� �����ϰų� ���� �� ���ڸ� �Է��ϼ���.\n");
        }

        // ���� �Է� ���ڿ� ����
        stackToString(&inputStack, currentInput);

        // ���� �Է� ���¿� ���� ��õ �ܾ� ���
        if (strlen(currentInput) == 0) {
            printf("��õ �ܾ�: ����\n");
        }
        else {
            printf("��õ �ܾ�: ");
            int found = 0;
            for (int i = 0; i < MAX_WORDS; i++) {
                if (isPrefix(currentInput, dictionary[i])) {
                    printf("%s ", dictionary[i]);
                    found = 1;
                }
            }
            if (!found) printf("����");
            printf("\n");
        }
    }

    return 0;
}
