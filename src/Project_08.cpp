/*
 * ���α׷���: ī�� �� �ùķ�����
 * ����:
 *   ���� ī�� ��(52��)�� ���� ī�� ����� �����ϴ� �ùķ������Դϴ�.
 *   ����ڴ� ��ɾ ���� ī�� �̱�, ī�� ��ȯ, �� ����, �� ���� Ȯ�� ���� ������ �� �ֽ��ϴ�.
 *
 * �ֿ� ���:
 *   1. �� �ʱ�ȭ: 52�� ī�� ���� (4���� ���� x 13���� ����)
 *   2. �� ����: Fisher-Yates �˰������� ������ ����
 *   3. ī�� �̱�: ������ ���� ��(top)�� �ִ� ī�� �ϳ��� ����
 *   4. ī�� ��ȯ: ���� ī�� ��Ͽ��� ���� �ֱ� ���� ī�带 ���� ��ȯ
 *   5. �� ���� ���: ���� ���� �����ִ� ī�� ���� ���̺� ī�� �� ǥ��
 *   6. ���� ī�� ��� ���: ���� ī����� ��ȣ�� �Բ� ���
 *
 * ����:
 *   draw    - ī�� �̱�
 *   return  - ���� �ֱٿ� ���� ī�� ���� ��ȯ
 *   shuffle - �� ����
 *   status  - ���� �� ���� �� ���� ī�� ��� ���
 *   exit    - ���α׷� ����
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_DECK 52      // ī�� �� �ִ� ũ�� (52��)
#define MAX_DRAWN 52     // ���� ī�� �ִ� ���� ����

 // ī�� ���� �̸� (����)
const char* suit_names[] = { "Heart", "Diamond", "Club", "Spade" };
// ī�� ���� �̸� (����)
const char* rank_names[] = {
    "A", "2", "3", "4", "5", "6", "7",
    "8", "9", "10", "J", "Q", "K"
};

// ī�� ���� ������ (0~3)
typedef enum { HEART, DIAMOND, CLUB, SPADE } Suit;
// ī�� ���� ������ (0~12)
typedef enum {
    ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
    EIGHT, NINE, TEN, JACK, QUEEN, KING
} Rank;

// ī�� ����ü: ���̿� ���� ����
typedef struct {
    Suit suit;   // ī�� ����
    Rank rank;   // ī�� ����
} Card;

// �� ����ü: ī�� �迭�� top �ε��� ����
typedef struct {
    Card cards[MAX_DECK]; // ī�� �迭
    int top;              // ���� ���� �� ī�� �ε��� (0~51, -1�̸� �� ��)
} Deck;

// ���� ī�� ��� ����ü: ī�� �迭�� ���� ����
typedef struct {
    Card drawn[MAX_DRAWN]; // ���� ī�� �迭
    int count;             // ���� ���� ī�� ����
} DrawnList;

/*
 * �� �ʱ�ȭ �Լ�
 *  - 52���� ī�� ����
 *  - suit�� HEART~SPADE ����
 *  - rank�� ACE~KING ����
 *  - top�� 51�� �����Ͽ� ���� ���� �� ���·� ����
 */
void initDeck(Deck* deck) {
    deck->top = MAX_DECK - 1;
    int idx = 0;
    for (int s = HEART; s <= SPADE; s++) {
        for (int r = ACE; r <= KING; r++) {
            deck->cards[idx].suit = (Suit)s;  // C ��Ÿ�� ĳ��Ʈ ����
            deck->cards[idx].rank = (Rank)r;  // C ��Ÿ�� ĳ��Ʈ ����
            idx++;
        }
    }
}

/*
 * ���� ī�� ��� �ʱ�ȭ �Լ�
 *  - count�� 0���� �ʱ�ȭ
 *  - �迭�� ī����� HEART-Ace�� �ʱ�ȭ (�� �ص� ����)
 */
void initDrawnList(DrawnList* list) {
    list->count = 0;
    for (int i = 0; i < MAX_DRAWN; i++) {
        list->drawn[i].suit = HEART;
        list->drawn[i].rank = ACE;
    }
}

/*
 * ī�� ��� �Լ�
 *  - �Է¹��� ī���� ���̿� ���ڸ� ����� ���
 *  - ��) Heart A, Diamond 10, Spade K
 */
void printCard(Card card) {
    printf("%s %s", suit_names[card.suit], rank_names[card.rank]);
}

/*
 * �� ���� �Լ�
 *  - Fisher-Yates �˰��� ����
 *  - ���� �õ�� ���� �ð� ���
 *  - ���� top �ε������� ������ ��ġ�� ī�� ��ȯ
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
 * ī�� �̱� �Լ�
 *  - ���� top ��ġ ī�� ��ȯ
 *  - top �ε��� 1 �����Ͽ� ī�� ���� ȿ��
 *  - ���� ������� ���� (0 ��ȯ)
 *  - ���� �� 1 ��ȯ �� ���� ī�� ��� ���ڷ� ����
 */
int drawCard(Deck* deck, Card* card) {
    if (deck->top < 0) return 0;  // �� �����
    *card = deck->cards[deck->top--]; // top ī�� ��ȯ �� ����
    return 1;
}

/*
 * ī�� ��ȯ �Լ�
 *  - ���� top �ε��� 1 ���� �� ī�� ����
 *  - ���� ���� �� ������ ���� (0 ��ȯ)
 *  - ���� �� 1 ��ȯ
 */
int returnCard(Deck* deck, Card card) {
    if (deck->top >= MAX_DECK - 1) return 0; // �� ���� ��
    deck->cards[++deck->top] = card;         // ī�� �߰�
    return 1;
}

/*
 * �� ���� ��� �Լ�
 *  - ���� ���� �����ִ� ī�� �� ���� ���
 *  - �� ���̺� ���� ī�� ���� ���
 *  - �������� ���� ���м� ���
 */
void printDeckStatus(Deck* deck) {
    int counts[4] = { 0, 0, 0, 0 };
    for (int i = 0; i <= deck->top; i++) {
        counts[deck->cards[i].suit]++;
    }
    printf("\n===== ���� �� ���� =====\n");
    printf("���� ī�� �� �� : %2d��\n", deck->top + 1);
    for (int i = 0; i < 4; i++) {
        printf("  %7s : %2d��\n", suit_names[i], counts[i]);
    }
    printf("======================\n");
}

/*
 * ���� ī�� ��� ��� �Լ�
 *  - ���� ī�尡 ������ [����] ���
 *  - ������ ��ȣ�� �Բ� �� �پ� ���
 *  - �������� ���� ���м� ���
 */
void printDrawnList(DrawnList* list) {
    printf("===== ���� ī�� ��� =====\n");
    if (list->count == 0) {
        printf("  [����]\n");
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
 * main �Լ� - ����� �Է� �� ��ɾ� ó��
 */
int main() {
    Deck deck;
    DrawnList drawnList;
    char command[20];
    Card card;

    initDeck(&deck);        // �� �ʱ�ȭ
    shuffleDeck(&deck);     // �� ����
    initDrawnList(&drawnList); // ���� ī�� ��� �ʱ�ȭ

    printf("ī�� �� �ùķ����� ����!\n");
    printf("��ɾ� ���:\n");
    printf("  draw    : ī�� �̱�\n");
    printf("  return  : ī�� ��ȯ\n");
    printf("  shuffle : �� ����\n");
    printf("  status  : �� ���� Ȯ��\n");
    printf("  exit    : ����\n");

    while (1) {
        printf("\n��ɾ� �Է� >> ");
        scanf("%s", command);

        if (strcmp(command, "draw") == 0) {
            if (drawCard(&deck, &card)) {
                if (drawnList.count < MAX_DRAWN) {
                    drawnList.drawn[drawnList.count++] = card;
                    printf("[�̱� ����] ���� ī��: ");
                    printCard(card);
                    printf("\n");
                }
                else {
                    printf("[����] ���� ī�� ����� ���� á���ϴ�.\n");
                }
            }
            else {
                printf("[�̱� ����] ���� ī�尡 �����ϴ�!\n");
            }
        }
        else if (strcmp(command, "return") == 0) {
            if (drawnList.count == 0) {
                printf("[��ȯ ����] ��ȯ�� ī�尡 �����ϴ�.\n");
                continue;
            }
            Card returnCard_ = drawnList.drawn[drawnList.count - 1];
            if (returnCard(&deck, returnCard_)) {
                printf("[��ȯ ����] ī�� ��ȯ: ");
                printCard(returnCard_);
                printf("\n");
                drawnList.count--;
            }
            else {
                printf("[��ȯ ����] ���� ���� ���� ī�带 ��ȯ�� �� �����ϴ�.\n");
            }
        }
        else if (strcmp(command, "shuffle") == 0) {
            shuffleDeck(&deck);
            printf("[���� �Ϸ�] ���� �������� �������ϴ�.\n");
        }
        else if (strcmp(command, "status") == 0) {
            printDeckStatus(&deck);
            printDrawnList(&drawnList);
        }
        else if (strcmp(command, "exit") == 0) {
            printf("���α׷��� �����մϴ�.\n");
            break;
        }
        else {
            printf("[����] �� �� ���� ��ɾ��Դϴ�. �ٽ� �Է��ϼ���.\n");
        }
    }

    return 0;
}
