# C Language Simulator & Algorithm Portfolio

## 1. 개요

이 리포지토리는 C 언어로 작성된 **시뮬레이터 및 알고리즘 과제** 프로젝트를 모아놓은 저장소입니다.  
각 `.cpp` 파일은 **독립적인 실행 파일**로 구성되어 있으며, 각각 `main()` 함수를 포함합니다.  
스택, 큐, 문자열, 시뮬레이션 기반 로직을 다양한 방식으로 구현한 프로젝트들입니다.

---

## 2. 프로젝트 목적

자료구조의 실제 동작을 시뮬레이션을 통해 직접 확인하고,  
스택/큐/배열 등을 기반으로 한 프로그램 구현 능력을 향상시키는 것이 목표입니다.  
학습 후 포트폴리오로 활용하기 적합하도록 구성되어 있습니다.

---

## 3. 파일 목록 및 설명

| 번호 | 파일명                                      | 설명 |
|------|---------------------------------------------|------|
| 01   | `01_Infix_to_Postfix_Program.cpp`           | **중위식 → 후위식 변환 + 계산기** |
| 02   | `02_Undo_Redo_Note_Program.cpp`             | **Undo/Redo 메모장 시뮬레이터** |
| 03   | `03_Maze_solving_algorithm.cpp`             | **미로 탐색 알고리즘 (DFS/BFS)** |
| 04   | `04_DNA_Base_Pair_Checker.cpp`              | **DNA 염기쌍 검사기 (A-T, G-C)** |
| 05   | `05_MP3_Playback_Simulator.cpp`             | **MP3 재생 시뮬레이터 (이전/다음)** |
| 06   | `06_Word_Auto-completion_Simulator.cpp`     | **단어 자동완성 시뮬레이터** |
| 07   | `07_Chat_Message_Management_Simulator.cpp`  | **채팅방 메시지 관리 시뮬레이터 (큐 기반)** |
| 08   | `08_Card_deck_Simulator.cpp`                | **카드 덱 시뮬레이터 (스택/큐 사용)** |

---

## 4. 실행 방법

각 `.cpp` 파일은 **독립적으로 컴파일 및 실행**할 수 있습니다.

예시) 1번 수식 계산기 예제 컴파일 및 실행

```bash 
g++ 01_Infix_to_Postfix_Program.cpp -o calc  
./calc
```

---

### 5. 개발 환경
- 언어: C (C99 기준)
- 컴파일러: gcc, clang
- 운영체제: Windows / Linux / macOS
- 개발 도구: Visual Studio, VS Code, Code::Blocks 등

---

### 6. 주요 학습 내용
- 스택, 큐, 배열 기반 자료구조 활용
- 문자열 처리 및 조건 검사 알고리즘
- 후위 표기법 계산, Undo/Redo 흐름 제어
- 미로 탐색(DFS/BFS 응용), DNA 쌍 체크 로직
- 채팅 메시지 큐 관리, 자동완성 시뮬레이션
- 카드 뽑기/셔플/반환 등 게임 기반 로직

---

### 7. 작성자
- 이름: 김근우 (컴퓨터공학과)
- GitHub: https://github.com/KimGeunWoo1028
- 이메일: jeunghyon1234@gmail.com

---

### 8. 라이센스
본 저장소의 코드는 **개인 학습용 및 참고용**으로 자유롭게 사용 가능합니다.  
단, 상업적 사용이나 무단 배포는 제한됩니다.
