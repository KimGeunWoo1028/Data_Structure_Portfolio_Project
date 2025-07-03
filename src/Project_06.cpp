/*
 * 프로그램명: 간단한 웹 채팅방 메시지 관리 시뮬레이터 (C언어)
 * 목적:
 *   - 사용자가 입력한 채팅 메시지를 순서대로 저장하고,
 *   - 현재 저장된 메시지를 확인하거나 마지막 메시지를 삭제할 수 있으며,
 *   - '/exit' 명령어로 프로그램을 종료할 수 있는 시뮬레이터.
 *
 * 기능:
 *   - 일반 문자열 입력 시 메시지로 저장됨.
 *   - '/view' 명령: 저장된 모든 메시지를 번호와 함께 출력.
 *   - '/delete' 명령: 가장 마지막에 저장된 메시지를 삭제.
 *   - '/exit' 명령: 프로그램 종료.
 *
 * 특징:
 *   - 구조체를 사용해 메시지를 배열에 저장하고, 메시지 개수를 추적.
 *   - 최대 메시지 수(MAX_MSG)와 메시지 길이(MAX_LEN)를 상수로 제한.
 *   - 실제 채팅 서버는 아니지만, 메시지 저장/관리의 기초 구조를 구현함.
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MSG 100     // 최대 저장할 수 있는 메시지 수
#define MAX_LEN 100     // 한 메시지의 최대 길이

 // 메시지를 저장하는 구조체 정의
typedef struct {
    char messages[MAX_MSG][MAX_LEN];  // 메시지를 저장하는 2차원 배열
    int count;                        // 현재 저장된 메시지 개수
} Chat;

// 메시지를 추가하는 함수
void addMessage(Chat* chat, const char* msg) {
    if (chat->count >= MAX_MSG) {
        // 최대 개수를 초과한 경우 에러 출력
        printf("메시지 저장 공간이 가득 찼습니다!\n");
        return;
    }

    // 새로운 메시지를 배열에 복사 (길이 초과 방지)
    strncpy(chat->messages[chat->count], msg, MAX_LEN - 1);
    chat->messages[chat->count][MAX_LEN - 1] = '\0'; // 널 종료 보장
    chat->count++; // 메시지 수 증가
}

// 저장된 모든 메시지를 출력하는 함수
void viewMessages(const Chat* chat) {
    if (chat->count == 0) {
        printf("저장된 메시지가 없습니다.\n");
        return;
    }

    printf("\n[ 전체 메시지 목록 ]\n");
    for (int i = 0; i < chat->count; i++) {
        printf("%2d: %s\n", i + 1, chat->messages[i]);  // 1번부터 출력
    }
    printf("----------------------\n");
}

// 마지막 메시지를 삭제하는 함수
void deleteLastMessage(Chat* chat) {
    if (chat->count == 0) {
        // 삭제할 메시지가 없을 경우
        printf("삭제할 메시지가 없습니다.\n");
        return;
    }

    // 가장 최근 메시지를 출력한 후 삭제
    printf("삭제된 메시지: %s\n", chat->messages[chat->count - 1]);
    chat->count--; // 메시지 수 감소
}

// 메인 함수
int main() {
    Chat chat;           // 메시지 저장용 구조체 변수 선언
    chat.count = 0;      // 메시지 수 초기화

    char input[MAX_LEN]; // 사용자 입력 저장용 문자열 배열

    // 프로그램 시작 메시지 및 명령어 안내
    printf("=== 간단한 웹 채팅방 메시지 시뮬레이터 ===\n");
    printf("명령어:\n");
    printf("  메시지 입력: 일반 문자열\n");
    printf("  /view       : 전체 메시지 보기\n");
    printf("  /delete     : 마지막 메시지 삭제\n");
    printf("  /exit       : 프로그램 종료\n");

    // 무한 루프: 사용자 입력을 계속해서 받음
    while (1) {
        printf("\n입력 >> ");
        fgets(input, sizeof(input), stdin); // 입력 받기 (공백 포함)

        // 입력 끝의 개행 문자('\n') 제거
        input[strcspn(input, "\n")] = '\0';

        // 입력이 '/exit'이면 종료
        if (strcmp(input, "/exit") == 0) {
            printf("채팅 종료.\n");
            break;
        }
        // 입력이 '/view'이면 전체 메시지 출력
        else if (strcmp(input, "/view") == 0) {
            viewMessages(&chat);
        }
        // 입력이 '/delete'이면 마지막 메시지 삭제
        else if (strcmp(input, "/delete") == 0) {
            deleteLastMessage(&chat);
        }
        // 일반 문자열 입력이면 메시지 저장
        else if (strlen(input) > 0) {
            addMessage(&chat, input);
            printf("메시지 저장 완료.\n");
        }
        // 빈 문자열 입력 처리
        else {
            printf("빈 입력은 저장되지 않습니다.\n");
        }
    }

    return 0; // 프로그램 종료
}