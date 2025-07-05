/*
  프로그램 개요:
  이 프로그램은 Depth First Search(DFS) 알고리즘을 사용하여
  2차원 미로에서 시작점 'S'에서 출구 'E'까지의 경로를 탐색하는 미로 탈출 시뮬레이터입니다.

  주요 기능:
  - 스택을 활용해 DFS 방식으로 미로를 탐색합니다.
  - 이동 가능한 경로(길 '0' 또는 출구 'E')를 따라 탐색하며,
    방문했던 곳은 다시 방문하지 않도록 처리합니다.
  - 출구에 도달하면 탐색 경로를 '*' 문자로 표시하여 출력합니다.
  - 경로가 없으면 실패 메시지를 출력합니다.

  입력:
  - 미로의 크기 (행과 열)
  - 미로 정보 (문자열): 'S'는 시작점, 'E'는 출구, '0'은 이동 가능한 길, '1'은 벽

  출력:
  - 경로가 존재할 경우 미로와 경로를 '*'로 표시한 결과 출력
  - 경로가 없으면 실패 메시지 출력

  내부 구조:
  - 스택 자료구조로 DFS 탐색을 구현
  - 방문 여부를 별도의 배열로 관리하여 중복 방문 방지
  - 백트래킹을 통해 경로 탐색
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX 100  // 미로 최대 크기 (100x100)

// 좌표를 나타내기 위한 구조체
typedef struct {
    int x, y;  // 미로 내에서의 행과 열 좌표
} Point;

// 스택 구조체 (Point 배열과 top 인덱스 포함)
typedef struct {
    Point data[MAX]; // 스택에 저장할 Point 배열
    int top;         // 스택의 최상단 인덱스 (비어있으면 -1)
} Stack;

// 스택 초기화 함수: 스택을 빈 상태로 설정 (top = -1)
void initStack(Stack* s) {
    s->top = -1;
}

// 스택이 비어있는지 확인하는 함수
// 비어있으면 1(true), 아니면 0(false) 반환
int isEmpty(Stack* s) {
    return s->top == -1;
}

// 스택이 가득 찼는지 확인하는 함수
// 가득 차면 1(true), 아니면 0(false) 반환
int isFull(Stack* s) {
    return s->top == MAX - 1;
}

// 스택에 새로운 Point 추가하기 (push 함수)
// 만약 스택이 가득 찼으면 오류 메시지 출력 후 종료
void push(Stack* s, Point p) {
    if (isFull(s)) {
        printf("스택이 가득 찼습니다!\n");
        exit(1);
    }
    s->data[++(s->top)] = p;  // top을 1 증가시키고 해당 위치에 값 저장
}

// 스택에서 마지막에 추가된 Point를 제거 및 반환 (pop 함수)
// 만약 스택이 비어있으면 오류 메시지 출력 후 종료
Point pop(Stack* s) {
    if (isEmpty(s)) {
        printf("스택이 비어있습니다!\n");
        exit(1);
    }
    return s->data[(s->top)--]; // 현재 top의 값을 반환 후 top 감소
}

// 스택의 마지막 요소를 확인하는 함수 (제거하지 않고 반환)
// 스택이 비어있으면 오류 메시지 출력 후 종료
Point peek(Stack* s) {
    if (isEmpty(s)) {
        printf("스택이 비어있습니다!\n");
        exit(1);
    }
    return s->data[s->top]; // top 위치의 Point 반환
}

// 미로 크기 및 미로 정보를 저장하는 전역 변수
int N, M;                // 미로의 행(N)과 열(M) 크기
char maze[MAX][MAX];     // 미로 배열: 문자로 저장 (S, E, 0, 1)
int visited[MAX][MAX];   // 방문 여부 배열 (1: 방문, 0: 미방문)

// 이동 방향 배열 (상, 하, 좌, 우 순서)
int dx[4] = { -1, 1, 0, 0 }; // 행 변화량
int dy[4] = { 0, 0, -1, 1 }; // 열 변화량

// 주어진 (x, y)가 미로 범위 내에 있는지 검사하는 함수
// 유효한 좌표이면 1(true), 아니면 0(false)
int isValid(int x, int y) {
    return (x >= 0 && x < N&& y >= 0 && y < M);
}

// 메인 함수: 미로 입력, DFS 탐색 수행 및 결과 출력
int main() {
    Point start, end; // 시작점(S)과 출구(E)의 좌표 저장 변수
    Stack stack;      // DFS 탐색용 스택
    initStack(&stack); // 스택 초기화

    // 1. 미로 크기 입력 받기
    printf("미로 크기 입력 (행 열): ");
    scanf("%d %d", &N, &M);

    // 2. 미로 정보 입력 및 시작점과 출구 위치 찾기
    printf("미로 입력 (S=시작, E=출구, 0=길, 1=벽):\n");
    for (int i = 0; i < N; i++) {
        scanf("%s", maze[i]);  // 한 행 문자열 입력
        for (int j = 0; j < M; j++) {
            // 시작점 좌표 저장
            if (maze[i][j] == 'S') {
                start.x = i;
                start.y = j;
            }
            // 출구 좌표 저장
            else if (maze[i][j] == 'E') {
                end.x = i;
                end.y = j;
            }
            visited[i][j] = 0;  // 방문 여부 초기화 (0: 방문 안함)
        }
    }

    // 3. 시작점을 스택에 넣고 방문 처리
    push(&stack, start);
    visited[start.x][start.y] = 1;

    int found = 0; // 출구에 도달했는지 여부 표시 (0: 미발견, 1: 발견)

    // 4. DFS 탐색: 스택이 비어있지 않은 동안 반복
    while (!isEmpty(&stack)) {
        Point cur = peek(&stack); // 현재 위치 확인 (스택 최상단)

        // 현재 위치가 출구라면 탐색 종료
        if (cur.x == end.x && cur.y == end.y) {
            found = 1; // 출구 발견 표시
            break;
        }

        int moved = 0; // 현재 위치에서 이동 성공 여부

        // 5. 네 방향(상, 하, 좌, 우) 탐색
        for (int dir = 0; dir < 4; dir++) {
            int nx = cur.x + dx[dir]; // 다음 행 위치
            int ny = cur.y + dy[dir]; // 다음 열 위치

            // 다음 위치가 미로 내부이고, 방문하지 않았고, 이동 가능한 곳인지 검사
            if (isValid(nx, ny) && !visited[nx][ny] && (maze[nx][ny] == '0' || maze[nx][ny] == 'E')) {
                visited[nx][ny] = 1;     // 방문 처리
                Point nextPos;           // 다음 위치 변수 선언
                nextPos.x = nx;
                nextPos.y = ny;
                push(&stack, nextPos);   // 스택에 다음 위치 추가
                moved = 1;               // 이동 성공 표시
                break;                   // 한 방향 이동 후 탐색 종료
            }
        }

        // 6. 네 방향 모두 이동할 수 없으면 현재 위치에서 되돌아감 (백트래킹)
        if (!moved) {
            pop(&stack); // 현재 위치 제거
        }
    }

    // 7. 탐색 결과 출력
    if (found) {
        printf("미로 탈출 성공! 경로 표시:\n");

        // 7-1. 원본 미로를 손상시키지 않기 위해 복사본 생성
        char maze_path[MAX][MAX];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                maze_path[i][j] = maze[i][j];

        // 7-2. 스택에 저장된 경로를 따라 '*' 문자로 표시 (S, E는 그대로)
        for (int i = 0; i <= stack.top; i++) {
            int x = stack.data[i].x;
            int y = stack.data[i].y;
            if (maze_path[x][y] != 'S' && maze_path[x][y] != 'E') {
                maze_path[x][y] = '*';
            }
        }

        // 7-3. 최종 미로 및 경로 출력 (행렬 형태로)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                printf("%c ", maze_path[i][j]);
            }
            printf("\n");
        }
    }
    else {
        // 출구까지의 경로를 찾지 못한 경우 메시지 출력
        printf("미로 탈출 실패!\n");
    }

    return 0; // 프로그램 정상 종료
}
