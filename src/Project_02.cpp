/*
================================================================================
프로그램명: 은행 업무 시뮬레이터
설명: 이 프로그램은 원형 큐를 사용하여 은행 업무 시뮬레이션을 수행합니다.
      고객들이 랜덤한 시간 간격으로 도착하며, 각 고객은 서비스 시간(업무 시간)을 가집니다.
      고객들은 큐에 들어간 후 순서대로 처리되며, 60초 동안 시뮬레이션이 진행됩니다.
================================================================================
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>      // 입력 및 출력 관련 함수 제공
#include <stdlib.h>     // rand, srand, malloc 등 메모리 관련 함수 제공
#include <time.h>       // 시간 관련 함수 제공 (time 함수)
#include <windows.h>    // Sleep 함수 사용을 위함 (윈도우에서 1초 대기 효과)

// 큐에 저장할 최대 고객 수 설정
#define MAX_QUEUE_SIZE 10 // 원형 큐의 최대 크기

// 고객 구조체: 고객의 번호와 업무 시간을 저장
typedef struct {
    int id;          // 고객 번호
    int serviceTime; // 고객 업무 시간 (초)
} Customer;

// 원형 큐 구조체: 고객 데이터를 저장하는 배열과 큐 관리 변수들
typedef struct {
    Customer data[MAX_QUEUE_SIZE]; // 고객 데이터를 저장할 배열
    int front;                     // 큐 앞쪽 인덱스
    int rear;                      // 큐 뒷쪽 인덱스
    int count;                     // 큐에 저장된 고객 수
} Queue;

// 큐 초기화 함수: front, rear, count를 0으로 초기화
void initQueue(Queue* q) {
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

// 큐가 비어있는지 확인하는 함수: count가 0이면 비어있음
int isEmpty(Queue* q) {
    return q->count == 0;
}

// 큐가 가득 찼는지 확인하는 함수: count가 MAX_QUEUE_SIZE와 같으면 가득 참
int isFull(Queue* q) {
    return q->count == MAX_QUEUE_SIZE;
}

// 큐에 고객을 추가하는 함수
// 큐가 가득 찬 경우, 고객 추가 불가 메시지를 출력하고 함수 종료
void enqueue(Queue* q, Customer item) {
    if (isFull(q)) {
        printf("[ 큐가 가득 찼습니다! 고객 %d는 대기열에 못 들어갑니다. ]\n", item.id);
        return;
    }
    q->data[q->rear] = item;                        // rear 위치에 고객 추가
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;         // 원형으로 rear 인덱스 업데이트
    q->count++;                                     // 큐에 고객 수 1 증가
    printf("[ 고객 %d 대기열에 추가 (업무시간: %d초) ]\n", item.id, item.serviceTime);
}

// 큐에서 고객을 꺼내는 함수
// 큐가 비었으면 기본값(-1)을 가진 Customer 반환
Customer dequeue(Queue* q) {
    Customer item = { -1, -1 }; // 기본값 설정
    if (isEmpty(q)) {
        return item;
    }
    item = q->data[q->front];                       // front 위치의 고객 데이터를 가져옴
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;       // 원형으로 front 인덱스 업데이트
    q->count--;                                     // 큐에 고객 수 1 감소
    return item;
}

// 고객 처리 시뮬레이션 함수
// 각 고객의 업무 시간을 카운트다운하며 처리하는 과정 시뮬레이션
void processCustomer(Customer c) {
    printf("지금 처리할 고객: 고객#%d\n", c.id);
    // 서비스 시간을 0까지 카운트다운 하며 1초 대기
    for (int i = c.serviceTime; i >= 0; i--) {
        printf("%d ", i);
        fflush(stdout);       // 출력 버퍼를 즉시 출력하기 위해 사용
        Sleep(1000);          // 1초 대기 (1000 밀리초)
    }
    printf("\n<고객 %d 처리 완료: %d초>\n\n", c.id, c.serviceTime);
}

int main() {
    // 시뮬레이션에 사용할 큐 초기화
    Queue q;
    initQueue(&q);

    // 랜덤 시드 초기화 (현재 시간 사용)
    srand((unsigned int)time(NULL));

    int currentTime = 0;                     // 시뮬레이션 시작 시각 (0초부터 시작)
    int nextArrival = rand() % 5 + 3;          // 첫 고객 도착 시간: 3~7초 사이 랜덤
    int customerID = 1;                      // 고객 ID 시작 번호

    // 시뮬레이션 시작 메시지 출력
    printf("=== 은행 업무 시뮬레이터 시작 ===\n");

    // 60초 시뮬레이션 루프
    while (1) {
        printf("현재 시각: %d초\n", currentTime);

        // 고객 도착 여부 확인: 현재 시각이 다음 도착 시간과 일치하면 새 고객 생성
        if (currentTime == nextArrival) {
            Customer newCustomer;
            newCustomer.id = customerID++;          // 고객 번호 설정 후 증가
            newCustomer.serviceTime = rand() % 11 + 5; // 서비스 시간: 5~15초 랜덤

            // 새 고객 도착 메시지 출력
            printf("[ 다음 고객 도착 : 고객#%d, 업무시간 %d초 ]\n", newCustomer.id, newCustomer.serviceTime);
            enqueue(&q, newCustomer);                // 큐에 새 고객 추가

            // 다음 고객 도착 시간 재설정 (현재 시각 + 3~7초 랜덤)
            nextArrival = currentTime + (rand() % 5 + 3);
        }

        // 큐에 대기 중인 고객이 있으면, 고객을 꺼내어 서비스 처리 시작
        if (!isEmpty(&q)) {
            Customer current = dequeue(&q);
            processCustomer(current);
        }
        else {
            // 큐가 비었으면 "대기중" 메시지 출력 후 1초 대기
            printf("처리할 고객 없음. 1초 대기 중...\n\n");
            Sleep(1000);
        }

        currentTime++;  // 현재 시각 1초 증가

        // 60초 시뮬레이션 종료
        if (currentTime > 60) break;
    }

    // 시뮬레이션 종료 메시지 출력
    printf("=== 시뮬레이션 종료 ===\n");
    return 0;
}
