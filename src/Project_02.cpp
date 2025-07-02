/*
  ���α׷� ����:
  �� ���α׷��� Depth First Search(DFS) �˰����� ����Ͽ�
  2���� �̷ο��� ������ 'S'���� �ⱸ 'E'������ ��θ� Ž���ϴ� �̷� Ż�� �ùķ������Դϴ�.

  �ֿ� ���:
  - ������ Ȱ���� DFS ������� �̷θ� Ž���մϴ�.
  - �̵� ������ ���(�� '0' �Ǵ� �ⱸ 'E')�� ���� Ž���ϸ�,
    �湮�ߴ� ���� �ٽ� �湮���� �ʵ��� ó���մϴ�.
  - �ⱸ�� �����ϸ� Ž�� ��θ� '*' ���ڷ� ǥ���Ͽ� ����մϴ�.
  - ��ΰ� ������ ���� �޽����� ����մϴ�.

  �Է�:
  - �̷��� ũ�� (��� ��)
  - �̷� ���� (���ڿ�): 'S'�� ������, 'E'�� �ⱸ, '0'�� �̵� ������ ��, '1'�� ��

  ���:
  - ��ΰ� ������ ��� �̷ο� ��θ� '*'�� ǥ���� ��� ���
  - ��ΰ� ������ ���� �޽��� ���

  ���� ����:
  - ���� �ڷᱸ���� DFS Ž���� ����
  - �湮 ���θ� ������ �迭�� �����Ͽ� �ߺ� �湮 ����
  - ��Ʈ��ŷ�� ���� ��� Ž��
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX 100  // �̷� �ִ� ũ�� (100x100)

// ��ǥ�� ��Ÿ���� ���� ����ü
typedef struct {
    int x, y;  // �̷� �������� ��� �� ��ǥ
} Point;

// ���� ����ü (Point �迭�� top �ε��� ����)
typedef struct {
    Point data[MAX]; // ���ÿ� ������ Point �迭
    int top;         // ������ �ֻ�� �ε��� (��������� -1)
} Stack;

// ���� �ʱ�ȭ �Լ�: ������ �� ���·� ���� (top = -1)
void initStack(Stack* s) {
    s->top = -1;
}

// ������ ����ִ��� Ȯ���ϴ� �Լ�
// ��������� 1(true), �ƴϸ� 0(false) ��ȯ
int isEmpty(Stack* s) {
    return s->top == -1;
}

// ������ ���� á���� Ȯ���ϴ� �Լ�
// ���� ���� 1(true), �ƴϸ� 0(false) ��ȯ
int isFull(Stack* s) {
    return s->top == MAX - 1;
}

// ���ÿ� ���ο� Point �߰��ϱ� (push �Լ�)
// ���� ������ ���� á���� ���� �޽��� ��� �� ����
void push(Stack* s, Point p) {
    if (isFull(s)) {
        printf("������ ���� á���ϴ�!\n");
        exit(1);
    }
    s->data[++(s->top)] = p;  // top�� 1 ������Ű�� �ش� ��ġ�� �� ����
}

// ���ÿ��� �������� �߰��� Point�� ���� �� ��ȯ (pop �Լ�)
// ���� ������ ��������� ���� �޽��� ��� �� ����
Point pop(Stack* s) {
    if (isEmpty(s)) {
        printf("������ ����ֽ��ϴ�!\n");
        exit(1);
    }
    return s->data[(s->top)--]; // ���� top�� ���� ��ȯ �� top ����
}

// ������ ������ ��Ҹ� Ȯ���ϴ� �Լ� (�������� �ʰ� ��ȯ)
// ������ ��������� ���� �޽��� ��� �� ����
Point peek(Stack* s) {
    if (isEmpty(s)) {
        printf("������ ����ֽ��ϴ�!\n");
        exit(1);
    }
    return s->data[s->top]; // top ��ġ�� Point ��ȯ
}

// �̷� ũ�� �� �̷� ������ �����ϴ� ���� ����
int N, M;                // �̷��� ��(N)�� ��(M) ũ��
char maze[MAX][MAX];     // �̷� �迭: ���ڷ� ���� (S, E, 0, 1)
int visited[MAX][MAX];   // �湮 ���� �迭 (1: �湮, 0: �̹湮)

// �̵� ���� �迭 (��, ��, ��, �� ����)
int dx[4] = { -1, 1, 0, 0 }; // �� ��ȭ��
int dy[4] = { 0, 0, -1, 1 }; // �� ��ȭ��

// �־��� (x, y)�� �̷� ���� ���� �ִ��� �˻��ϴ� �Լ�
// ��ȿ�� ��ǥ�̸� 1(true), �ƴϸ� 0(false)
int isValid(int x, int y) {
    return (x >= 0 && x < N&& y >= 0 && y < M);
}

// ���� �Լ�: �̷� �Է�, DFS Ž�� ���� �� ��� ���
int main() {
    Point start, end; // ������(S)�� �ⱸ(E)�� ��ǥ ���� ����
    Stack stack;      // DFS Ž���� ����
    initStack(&stack); // ���� �ʱ�ȭ

    // 1. �̷� ũ�� �Է� �ޱ�
    printf("�̷� ũ�� �Է� (�� ��): ");
    scanf("%d %d", &N, &M);

    // 2. �̷� ���� �Է� �� �������� �ⱸ ��ġ ã��
    printf("�̷� �Է� (S=����, E=�ⱸ, 0=��, 1=��):\n");
    for (int i = 0; i < N; i++) {
        scanf("%s", maze[i]);  // �� �� ���ڿ� �Է�
        for (int j = 0; j < M; j++) {
            // ������ ��ǥ ����
            if (maze[i][j] == 'S') {
                start.x = i;
                start.y = j;
            }
            // �ⱸ ��ǥ ����
            else if (maze[i][j] == 'E') {
                end.x = i;
                end.y = j;
            }
            visited[i][j] = 0;  // �湮 ���� �ʱ�ȭ (0: �湮 ����)
        }
    }

    // 3. �������� ���ÿ� �ְ� �湮 ó��
    push(&stack, start);
    visited[start.x][start.y] = 1;

    int found = 0; // �ⱸ�� �����ߴ��� ���� ǥ�� (0: �̹߰�, 1: �߰�)

    // 4. DFS Ž��: ������ ������� ���� ���� �ݺ�
    while (!isEmpty(&stack)) {
        Point cur = peek(&stack); // ���� ��ġ Ȯ�� (���� �ֻ��)

        // ���� ��ġ�� �ⱸ��� Ž�� ����
        if (cur.x == end.x && cur.y == end.y) {
            found = 1; // �ⱸ �߰� ǥ��
            break;
        }

        int moved = 0; // ���� ��ġ���� �̵� ���� ����

        // 5. �� ����(��, ��, ��, ��) Ž��
        for (int dir = 0; dir < 4; dir++) {
            int nx = cur.x + dx[dir]; // ���� �� ��ġ
            int ny = cur.y + dy[dir]; // ���� �� ��ġ

            // ���� ��ġ�� �̷� �����̰�, �湮���� �ʾҰ�, �̵� ������ ������ �˻�
            if (isValid(nx, ny) && !visited[nx][ny] && (maze[nx][ny] == '0' || maze[nx][ny] == 'E')) {
                visited[nx][ny] = 1;     // �湮 ó��
                Point nextPos;           // ���� ��ġ ���� ����
                nextPos.x = nx;
                nextPos.y = ny;
                push(&stack, nextPos);   // ���ÿ� ���� ��ġ �߰�
                moved = 1;               // �̵� ���� ǥ��
                break;                   // �� ���� �̵� �� Ž�� ����
            }
        }

        // 6. �� ���� ��� �̵��� �� ������ ���� ��ġ���� �ǵ��ư� (��Ʈ��ŷ)
        if (!moved) {
            pop(&stack); // ���� ��ġ ����
        }
    }

    // 7. Ž�� ��� ���
    if (found) {
        printf("�̷� Ż�� ����! ��� ǥ��:\n");

        // 7-1. ���� �̷θ� �ջ��Ű�� �ʱ� ���� ���纻 ����
        char maze_path[MAX][MAX];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                maze_path[i][j] = maze[i][j];

        // 7-2. ���ÿ� ����� ��θ� ���� '*' ���ڷ� ǥ�� (S, E�� �״��)
        for (int i = 0; i <= stack.top; i++) {
            int x = stack.data[i].x;
            int y = stack.data[i].y;
            if (maze_path[x][y] != 'S' && maze_path[x][y] != 'E') {
                maze_path[x][y] = '*';
            }
        }

        // 7-3. ���� �̷� �� ��� ��� (��� ���·�)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                printf("%c ", maze_path[i][j]);
            }
            printf("\n");
        }
    }
    else {
        // �ⱸ������ ��θ� ã�� ���� ��� �޽��� ���
        printf("�̷� Ż�� ����!\n");
    }

    return 0; // ���α׷� ���� ����
}
