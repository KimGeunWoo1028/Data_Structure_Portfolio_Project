/*
  프로그램명: 간단한 웹 채팅방 메시지 관리 시뮬레이터
  목적:
    - 채팅 메시지를 큐(FIFO 구조)에 저장
    - 큐의 최대 용량을 초과하면 가장 오래된 메시지를 자동 삭제
    - 사용자 명령에 따라 메시지를 추가, 삭제, 전체 출력
  특징:
    - 원형 큐 구조 사용 (고정된 버퍼 내에서 메모리 재사용)
    - "send"로 메시지 추가
    - "view"로 모든 메시지 출력
    - "delete"로 가장 오래된 메시지 수동 삭제
    - "exit"으로 종료
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MESSAGES 10     // 큐에 저장 가능한 최대 메시지 수
#define MAX_LEN 100        // 한 메시지의 최대 길이

// 큐 구조체 정의
typedef struct {
    char messages[MAX_MESSAGES][MAX_LEN]; // 메시지 저장 배열 (2차원)
    int front;  // 가장 오래된 메시지 위치
    int rear;   // 가장 마지막에 추가된 메시지 위치
    int size;   // 현재 큐에 저장된 메시지 수
} MessageQueue;

// 큐 초기화 함수
void initQueue(MessageQueue* q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

// 큐가 비어있는지 확인
int isEmpty(MessageQueue* q) {
    return q->size == 0;
}

// 큐가 가득 찼는지 확인
int isFull(MessageQueue* q) {
    return q->size == MAX_MESSAGES;
}

// 큐에 메시지 추가 (enqueue)
void enqueue(MessageQueue* q, const char* msg) {
    if (isFull(q)) {
        // 큐가 가득 찼으면 가장 오래된 메시지를 먼저 제거
        printf("[자동 삭제] 메시지 초과로 오래된 메시지 제거: %s\n", q->messages[q->front]);
        q->front = (q->front + 1) % MAX_MESSAGES;
        q->size--;
    }
    // 새로운 메시지 추가
    q->rear = (q->rear + 1) % MAX_MESSAGES;
    strcpy(q->messages[q->rear], msg);
    q->size++;
    printf("[메시지 추가] %s\n", msg);
}

// 큐에서 메시지 삭제 (dequeue)
void dequeue(MessageQueue* q) {
    if (isEmpty(q)) {
        printf("삭제할 메시지가 없습니다.\n");
        return;
    }
    printf("[메시지 삭제] %s\n", q->messages[q->front]);
    q->front = (q->front + 1) % MAX_MESSAGES;
    q->size--;
}

// 큐의 모든 메시지 출력
void viewMessages(MessageQueue* q) {
    if (isEmpty(q)) {
        printf("[대화 없음]\n");
        return;
    }
    printf("\n[채팅 메시지 목록] (최신 순 아님)\n");
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

    printf("=== 간단한 웹 채팅방 메시지 관리 시뮬레이터 ===\n");
    printf("명령어 목록: send / view / delete / exit\n");

    while (1) {
        printf("\n> 명령어 입력: ");
        scanf("%s", command);

        if (strcmp(command, "send") == 0) {
            getchar();  // 공백 문자 제거
            printf("보낼 메시지: ");
            fgets(message, sizeof(message), stdin);
            message[strcspn(message, "\n")] = '\0'; // 개행 문자 제거
            enqueue(&chatQueue, message);
        }
        else if (strcmp(command, "view") == 0) {
            viewMessages(&chatQueue);
        }
        else if (strcmp(command, "delete") == 0) {
            dequeue(&chatQueue);
        }
        else if (strcmp(command, "exit") == 0) {
            printf("프로그램 종료\n");
            break;
        }
        else {
            printf("잘못된 명령어입니다. 다시 시도하세요.\n");
        }
    }

    return 0;
}