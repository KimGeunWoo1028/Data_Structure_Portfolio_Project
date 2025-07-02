/*
 * 프로그램명: 단어 자동완성 시뮬레이터 (C언어)
 * 설명:
 *   사용자가 문자 하나씩 입력하면 현재 입력된 문자열을 관리하고,
 *   Undo(/u), Redo(/r) 기능을 지원하는 간단한 자동완성 시뮬레이터입니다.
 *
 *   - 입력 문자는 스택에 저장하여 문자열 상태 관리
 *   - Undo 명령은 최근 입력 문자 하나를 입력 스택에서 빼서 Undo 스택에 저장
 *   - Redo 명령은 Undo 스택에서 문자를 다시 입력 스택에 복원
 *   - 입력 상태를 바탕으로 미리 정의된 단어 사전에서 현재 입력 문자열로 시작하는 단어들을 추천
 *
 * 사용법:
 *   문자 한 글자를 입력하면 현재 입력에 추가되고, 추천 단어가 출력됩니다.
 *   명령어는 '/'로 시작하며 다음을 지원합니다.
 *     /u : Undo (입력한 문자 하나 되돌리기)
 *     /r : Redo (Undo한 문자 다시 입력하기)
 *     /q : 종료
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_INPUT_SIZE 100    // 최대 입력 문자 수
#define MAX_UNDO_SIZE 100     // Undo 스택 최대 크기 (입력과 동일)
#define MAX_WORDS 10          // 사전 단어 수
#define MAX_WORD_LEN 20       // 단어 최대 길이

 // 문자 스택 구조체 정의
typedef struct {
    char data[MAX_INPUT_SIZE]; // 문자 저장 배열
    int top;                   // 스택 최상단 인덱스
} CharStack;

// 스택 초기화 함수: top을 -1로 설정하여 빈 상태로 만듦
void initStack(CharStack* s) {
    s->top = -1;
}

// 스택이 비었는지 확인하는 함수
int isEmpty(CharStack* s) {
    return s->top == -1;
}

// 스택에 문자 넣기 (push)
// 성공 시 1 반환, 실패 시 0 반환 (스택 가득 찼을 때)
int push(CharStack* s, char ch) {
    if (s->top >= MAX_INPUT_SIZE - 1) return 0; // 스택이 가득 찼음
    s->data[++(s->top)] = ch;
    return 1;
}

// 스택에서 문자 빼기 (pop)
// 성공 시 1 반환하고 *ch에 문자 저장, 실패 시 0 반환 (스택 비었을 때)
int pop(CharStack* s, char* ch) {
    if (isEmpty(s)) return 0;
    *ch = s->data[(s->top)--];
    return 1;
}

// 스택에 저장된 문자를 문자열로 변환하여 out에 저장
// bottom(0)부터 top까지 순서대로 복사하고 끝에 널문자('\0') 추가
void stackToString(CharStack* s, char* out) {
    int i;
    for (i = 0; i <= s->top; i++) {
        out[i] = s->data[i];
    }
    out[i] = '\0';
}

// prefix가 word의 접두사인지 확인하는 함수 (대소문자 구분 없이)
// prefix가 word 시작 부분과 일치하면 1 반환, 아니면 0 반환
int isPrefix(const char* prefix, const char* word) {
    while (*prefix && *word) {
        if (tolower(*prefix) != tolower(*word)) return 0;
        prefix++;
        word++;
    }
    return *prefix == '\0'; // prefix 문자열이 끝났으면 접두사 맞음
}

int main() {
    CharStack inputStack;  // 현재 입력 문자열 저장용 스택
    CharStack undoStack;   // Undo된 문자 저장용 스택 (Redo용)
    initStack(&inputStack);
    initStack(&undoStack);

    // 자동완성 후보 단어 리스트 (사전)
    const char* dictionary[MAX_WORDS] = {
        "apple", "banana", "grape", "orange", "melon",
        "apricot", "blueberry", "blackberry", "pear", "peach"
    };

    char command[20];            // 사용자 입력 버퍼
    char currentInput[MAX_INPUT_SIZE]; // 현재 입력 문자열
    char ch;                    // 문자 저장용 변수

    // 프로그램 안내 메시지 출력
    printf("자동완성 시뮬레이터 시작\n");
    printf("명령어: 문자 입력 | /u: undo | /r: redo | /q: 종료\n");
    printf("예) 문자 입력: a\n");
    printf("    undo: /u\n");
    printf("    redo: /r\n");
    printf("    종료: /q\n");

    while (1) {
        // 현재 입력 문자열을 스택에서 문자열로 변환
        stackToString(&inputStack, currentInput);

        // 사용자에게 현재 상태와 입력 대기 표시
        printf("현재 입력: '%s' > ", currentInput);

        // 입력 받기
        if (fgets(command, sizeof(command), stdin) == NULL) break;

        // 입력 끝의 개행문자 제거
        size_t len = strlen(command);
        if (len > 0 && command[len - 1] == '\n')
            command[len - 1] = '\0';

        // 빈 입력 처리
        if (strlen(command) == 0) {
            printf("입력이 비었습니다. 다시 입력해주세요.\n");
            continue;
        }

        if (command[0] == '/') {
            // 슬래시로 시작하면 명령어 처리
            if (strcmp(command, "/q") == 0) {
                // 종료 명령
                printf("종료합니다.\n");
                break;
            }
            else if (strcmp(command, "/u") == 0) {
                // Undo 명령: 입력 스택에서 문자 하나 빼서 undo 스택에 저장
                if (pop(&inputStack, &ch)) {
                    push(&undoStack, ch);
                }
                else {
                    printf("Undo 불가: 입력된 문자가 없습니다.\n");
                }
            }
            else if (strcmp(command, "/r") == 0) {
                // Redo 명령: undo 스택에서 문자 하나 빼서 입력 스택에 다시 넣음
                if (pop(&undoStack, &ch)) {
                    push(&inputStack, ch);
                }
                else {
                    printf("Redo 불가: 되돌린 문자가 없습니다.\n");
                }
            }
            else {
                // 알 수 없는 명령어 처리
                printf("알 수 없는 명령어입니다.\n");
            }
        }
        else if (strlen(command) == 1) {
            // 문자 하나 입력받은 경우
            ch = command[0];
            if (!push(&inputStack, ch)) {
                // 스택이 꽉 찼을 때 처리
                printf("입력 스택이 가득 찼습니다.\n");
            }
            else {
                // 새 문자 입력 시 redo 스택 초기화
                initStack(&undoStack);
            }
        }
        else {
            // 길이가 1보다 크고 명령어가 아닌 잘못된 입력 처리
            printf("잘못된 입력입니다. 명령어는 '/'로 시작하거나 문자 한 글자만 입력하세요.\n");
        }

        // 현재 입력 문자열 갱신
        stackToString(&inputStack, currentInput);

        // 현재 입력 상태에 따른 추천 단어 출력
        if (strlen(currentInput) == 0) {
            printf("추천 단어: 없음\n");
        }
        else {
            printf("추천 단어: ");
            int found = 0;
            for (int i = 0; i < MAX_WORDS; i++) {
                if (isPrefix(currentInput, dictionary[i])) {
                    printf("%s ", dictionary[i]);
                    found = 1;
                }
            }
            if (!found) printf("없음");
            printf("\n");
        }
    }

    return 0;
}
