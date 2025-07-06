# 🧠 C Language Simulator & Algorithm Portfolio

이 리포지토리는 **C 언어로 작성한 시뮬레이터 및 알고리즘 프로젝트**들을 모아놓은 포트폴리오용 저장소입니다.  
각 `.cpp` 파일은 **독립 실행 프로그램**이며 `main()` 함수를 포함합니다.

---

## 🎯 프로젝트 목적

- 자료구조(스택, 큐, 배열 등)의 실제 동작을 시뮬레이션으로 구현
- 문자열 처리, 흐름 제어, 조건 검사 등 알고리즘 실습
- 실전 포트폴리오로 활용 가능한 C언어 기반 실습 프로젝트 구성

---

## 📂 프로젝트 목록

| 번호 | 파일명 | 설명 | 링크 |
|------|--------|------|------|
| 01 | `01_Infix_to_Postfix_Program.cpp` | 중위식 → 후위식 변환 및 계산기 | [🔗바로가기](src/01_Infix_to_Postfix_Program.cpp) |
| 02 | `02_Undo_Redo_Note_Program.cpp` | Undo/Redo 메모장 시뮬레이터 | [🔗바로가기](src/02_Undo_Redo_Note_Program.cpp) |
| 03 | `03_Maze_solving_algorithm.cpp` | 미로 탐색 알고리즘 (DFS) | [🔗바로가기](src/03_Maze_solving_algorithm.cpp) |
| 04 | `04_DNA_Base_Pair_Checker.cpp` | DNA 염기쌍 검사기 (A-T, G-C 확인) | [🔗바로가기](src/04_DNA_Base_Pair_Checker.cpp) |
| 05 | `05_MP3_Playback_Simulator.cpp` | MP3 재생 시뮬레이터 (이전/다음 곡) | [🔗바로가기](src/05_MP3_Playback_Simulator.cpp) |
| 06 | `06_Word_Auto-completion_Simulator.cpp` | 단어 자동완성 시뮬레이터 | [🔗바로가기](src/06_Word_Auto-completion_Simulator.cpp) |
| 07 | `07_Chat_Message_Management_Simulator.cpp` | 채팅방 메시지 관리 시뮬레이터 (큐 기반) | [🔗바로가기](src/07_Chat_Message_Management_Simulator.cpp) |
| 08 | `08_Card_deck_Simulator.cpp` | 카드 덱 시뮬레이터 (스택/큐 활용) | [🔗바로가기](src/08_Card_deck_Simulator.cpp) |

---

## ⚙️ 실행 방법

각 `.cpp` 파일은 개별적으로 컴파일 및 실행할 수 있습니다.

```bash
# 예시 - 1번 수식 계산기
gcc 01_Infix_to_Postfix_Program.cpp -o calc
./calc
```

---

## 💻 개발 환경

- 언어: C 
- 컴파일러: gcc, clang
- 운영체제: Windows / Linux / macOS
- 개발 도구: Visual Studio

---

## 🧠 주요 학습 내용

- 스택, 큐, 배열 기반 자료구조 응용
- 문자열 처리 및 조건 검사 알고리즘
- 후위 표기법 계산, Undo/Redo 흐름 제어
- DFS 기반 미로 탐색
- DNA 쌍 매칭 알고리즘
- 채팅 메시지 큐 시뮬레이션
- 자동완성 및 카드 게임 로직 구현
  
---

## 👨‍💻 작성자

- 이름: 김근우
- 전공: 컴퓨터공학과
- GitHub: https://github.com/KimGeunWoo1028
- 이메일: jeunghyon1234@gmail.com

---

## 📄 라이센스

본 저장소의 코드는 **개인 학습용 및 참고용**으로 자유롭게 사용 가능합니다.  
단, 상업적 사용이나 무단 배포는 제한됩니다.
