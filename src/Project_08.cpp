/*
 * 프로그램명: 카드 덱 시뮬레이터
 * 목적:
 *   실제 카드 덱(52장)과 뽑은 카드 목록을 관리하는 시뮬레이터입니다.
 *   사용자는 명령어를 통해 카드 뽑기, 카드 반환, 덱 섞기, 덱 상태 확인 등을 수행할 수 있습니다.
 *
 * 주요 기능:
 *   1. 덱 초기화: 52장 카드 생성 (4가지 무늬 x 13가지 숫자)
 *   2. 덱 섞기: Fisher-Yates 알고리즘으로 무작위 섞기
 *   3. 카드 뽑기: 덱에서 가장 위(top)에 있는 카드 하나를 뽑음
 *   4. 카드 반환: 뽑은 카드 목록에서 가장 최근 뽑은 카드를 덱에 반환
 *   5. 덱 상태 출력: 현재 덱에 남아있는 카드 수와 무늬별 카드 수 표시
 *   6. 뽑은 카드 목록 출력: 뽑은 카드들을 번호와 함께 출력
 *
 * 사용법:
 *   draw    - 카드 뽑기
 *   return  - 가장 최근에 뽑은 카드 덱에 반환
 *   shuffle - 덱 섞기
 *   status  - 현재 덱 상태 및 뽑은 카드 목록 출력
 *   exit    - 프로그램 종료
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_DECK 52      // 카드 덱 최대 크기 (52장)
#define MAX_DRAWN 52     // 뽑은 카드 최대 저장 개수

 // 카드 무늬 이름 (영어)
const char* suit_names[] = { "Heart", "Diamond", "Club", "Spade" };
// 카드 숫자 이름 (영어)
const char* rank_names[] = {
    "A", "2", "3", "4", "5", "6", "7",
    "8", "9", "10", "J", "Q", "K"
};

// 카드 무늬 열거형 (0~3)
typedef enum { HEART, DIAMOND, CLUB, SPADE } Suit;
// 카드 숫자 열거형 (0~12)
typedef enum {
    ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
    EIGHT, NINE, TEN, JACK, QUEEN, KING
} Rank;

// 카드 구조체: 무늬와 숫자 포함
typedef struct {
    Suit suit;   // 카드 무늬
    Rank rank;   // 카드 숫자
} Card;

// 덱 구조체: 카드 배열과 top 인덱스 포함
typedef struct {
    Card cards[MAX_DECK]; // 카드 배열
    int top;              // 덱의 가장 위 카드 인덱스 (0~51, -1이면 빈 덱)
} Deck;

// 뽑은 카드 목록 구조체: 카드 배열과 개수 포함
typedef struct {
    Card drawn[MAX_DRAWN]; // 뽑은 카드 배열
    int count;             // 현재 뽑은 카드 개수
} DrawnList;

/*
 * 덱 초기화 함수
 *  - 52장의 카드 생성
 *  - suit는 HEART~SPADE 순서
 *  - rank는 ACE~KING 순서
 *  - top을 51로 설정하여 덱이 가득 찬 상태로 만듦
 */
void initDeck(Deck* deck) {
    deck->top = MAX_DECK - 1;
    int idx = 0;
    for (int s = HEART; s <= SPADE; s++) {
        for (int r = ACE; r <= KING; r++) {
            deck->cards[idx].suit = (Suit)s;  // C 스타일 캐스트 적용
            deck->cards[idx].rank = (Rank)r;  // C 스타일 캐스트 적용
            idx++;
        }
    }
}

/*
 * 뽑은 카드 목록 초기화 함수
 *  - count를 0으로 초기화
 *  - 배열의 카드들을 HEART-Ace로 초기화 (안 해도 무방)
 */
void initDrawnList(DrawnList* list) {
    list->count = 0;
    for (int i = 0; i < MAX_DRAWN; i++) {
        list->drawn[i].suit = HEART;
        list->drawn[i].rank = ACE;
    }
}

/*
 * 카드 출력 함수
 *  - 입력받은 카드의 무늬와 숫자를 영어로 출력
 *  - 예) Heart A, Diamond 10, Spade K
 */
void printCard(Card card) {
    printf("%s %s", suit_names[card.suit], rank_names[card.rank]);
}

/*
 * 덱 섞기 함수
 *  - Fisher-Yates 알고리즘 적용
 *  - 랜덤 시드로 현재 시간 사용
 *  - 덱의 top 인덱스까지 무작위 위치와 카드 교환
 */
void shuffleDeck(Deck* deck) {
    srand((unsigned int)time(NULL));
    for (int i = deck->top; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
}

/*
 * 카드 뽑기 함수
 *  - 덱의 top 위치 카드 반환
 *  - top 인덱스 1 감소하여 카드 제거 효과
 *  - 덱이 비었으면 실패 (0 반환)
 *  - 성공 시 1 반환 및 뽑은 카드 출력 인자로 전달
 */
int drawCard(Deck* deck, Card* card) {
    if (deck->top < 0) return 0;  // 덱 비었음
    *card = deck->cards[deck->top--]; // top 카드 반환 후 감소
    return 1;
}

/*
 * 카드 반환 함수
 *  - 덱의 top 인덱스 1 증가 후 카드 저장
 *  - 덱이 가득 차 있으면 실패 (0 반환)
 *  - 성공 시 1 반환
 */
int returnCard(Deck* deck, Card card) {
    if (deck->top >= MAX_DECK - 1) return 0; // 덱 가득 참
    deck->cards[++deck->top] = card;         // 카드 추가
    return 1;
}

/*
 * 덱 상태 출력 함수
 *  - 현재 덱에 남아있는 카드 총 개수 출력
 *  - 각 무늬별 남은 카드 개수 출력
 *  - 가독성을 위해 구분선 출력
 */
void printDeckStatus(Deck* deck) {
    int counts[4] = { 0, 0, 0, 0 };
    for (int i = 0; i <= deck->top; i++) {
        counts[deck->cards[i].suit]++;
    }
    printf("\n===== 현재 덱 상태 =====\n");
    printf("남은 카드 총 수 : %2d장\n", deck->top + 1);
    for (int i = 0; i < 4; i++) {
        printf("  %7s : %2d장\n", suit_names[i], counts[i]);
    }
    printf("======================\n");
}

/*
 * 뽑은 카드 목록 출력 함수
 *  - 뽑은 카드가 없으면 [없음] 출력
 *  - 있으면 번호와 함께 한 줄씩 출력
 *  - 가독성을 위해 구분선 출력
 */
void printDrawnList(DrawnList* list) {
    printf("===== 뽑은 카드 목록 =====\n");
    if (list->count == 0) {
        printf("  [없음]\n");
    }
    else {
        for (int i = 0; i < list->count; i++) {
            printf("  %2d. ", i + 1);
            printCard(list->drawn[i]);
            printf("\n");
        }
    }
    printf("=========================\n");
}

/*
 * main 함수 - 사용자 입력 및 명령어 처리
 */
int main() {
    Deck deck;
    DrawnList drawnList;
    char command[20];
    Card card;

    initDeck(&deck);        // 덱 초기화
    shuffleDeck(&deck);     // 덱 섞기
    initDrawnList(&drawnList); // 뽑은 카드 목록 초기화

    printf("카드 덱 시뮬레이터 시작!\n");
    printf("명령어 목록:\n");
    printf("  draw    : 카드 뽑기\n");
    printf("  return  : 카드 반환\n");
    printf("  shuffle : 덱 섞기\n");
    printf("  status  : 덱 상태 확인\n");
    printf("  exit    : 종료\n");

    while (1) {
        printf("\n명령어 입력 >> ");
        scanf("%s", command);

        if (strcmp(command, "draw") == 0) {
            if (drawCard(&deck, &card)) {
                if (drawnList.count < MAX_DRAWN) {
                    drawnList.drawn[drawnList.count++] = card;
                    printf("[뽑기 성공] 뽑은 카드: ");
                    printCard(card);
                    printf("\n");
                }
                else {
                    printf("[오류] 뽑은 카드 목록이 가득 찼습니다.\n");
                }
            }
            else {
                printf("[뽑기 실패] 덱에 카드가 없습니다!\n");
            }
        }
        else if (strcmp(command, "return") == 0) {
            if (drawnList.count == 0) {
                printf("[반환 실패] 반환할 카드가 없습니다.\n");
                continue;
            }
            Card returnCard_ = drawnList.drawn[drawnList.count - 1];
            if (returnCard(&deck, returnCard_)) {
                printf("[반환 성공] 카드 반환: ");
                printCard(returnCard_);
                printf("\n");
                drawnList.count--;
            }
            else {
                printf("[반환 실패] 덱이 가득 차서 카드를 반환할 수 없습니다.\n");
            }
        }
        else if (strcmp(command, "shuffle") == 0) {
            shuffleDeck(&deck);
            printf("[섞기 완료] 덱을 무작위로 섞었습니다.\n");
        }
        else if (strcmp(command, "status") == 0) {
            printDeckStatus(&deck);
            printDrawnList(&drawnList);
        }
        else if (strcmp(command, "exit") == 0) {
            printf("프로그램을 종료합니다.\n");
            break;
        }
        else {
            printf("[오류] 알 수 없는 명령어입니다. 다시 입력하세요.\n");
        }
    }

    return 0;
}
