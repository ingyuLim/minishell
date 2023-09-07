#include <stdio.h>
#include <string.h>

// 유한 오토마타의 상태 열거형
typedef enum {
	START,					// 명령어의 시작
	PIPE,					// |
	IN_REDIRECT,			// <
	OUT_REDIRECT,			// >
	FILENAME,				// 파일 이름
	DOUBLE_IN_REDIRECT,		// <<
	DOUBLE_OUT_REDIRECT,	// >>
	OPEN_PAREN,				// (
	CLOSE_PAREN,			// )
	AND_OPERATOR,			// &&
	OR_OPERATOR				// ||
} State;

int main() {
	char	input_string[] = "command1 | (command2 && command3) < input.txt >> output.txt || command4";
	char	*token = strtok(input_string, " "); // 입력 문자열을 공백을 기준으로 토큰화

	State	current_state = START;
	int		paren_count = 0; // 괄호 쌍 개수를 추적하기 위한 변수
	int		logical_operator_expected = 0; // 논리 연산자가 기대되는지 여부를 추적하기 위한 변수

	while (token != NULL) {
		if (strcmp(token, "|") == 0) {
			if (current_state != FILENAME) {
				printf("유효하지 않은 명령어입니다.\n");
				return 1;
			}
			current_state = PIPE;
			logical_operator_expected = 0;
		} else if (strcmp(token, "<") == 0) {
			if (current_state != FILENAME) {
				printf("유효하지 않은 명령어입니다.\n");
				return 1;
			}
			current_state = IN_REDIRECT;
			logical_operator_expected = 0;
		} else if (strcmp(token, ">") == 0) {
			if (current_state != FILENAME) {
				printf("유효하지 않은 명령어입니다.\n");
				return 1;
			}
			current_state = OUT_REDIRECT;
			logical_operator_expected = 0;
		} else if (strcmp(token, "<<") == 0) {
			if (current_state != FILENAME) {
				printf("유효하지 않은 명령어입니다.\n");
				return 1;
			}
			current_state = DOUBLE_IN_REDIRECT;
			logical_operator_expected = 0;
		} else if (strcmp(token, ">>") == 0) {
			if (current_state != FILENAME) {
				printf("유효하지 않은 명령어입니다.\n");
				return 1;
			}
			current_state = DOUBLE_OUT_REDIRECT;
			logical_operator_expected = 0;
		} else if (strcmp(token, "(") == 0) {
			if (logical_operator_expected) {
				printf("유효하지 않은 명령어입니다.\n");
				return 1;
			}
			current_state = OPEN_PAREN;
			paren_count++;
		} else if (strcmp(token, ")") == 0) {
			if (current_state != FILENAME) {
				printf("유효하지 않은 명령어입니다.\n");
				return 1;
			}
			current_state = CLOSE_PAREN;
			paren_count--;
		} else if (strcmp(token, "&&") == 0 || strcmp(token, "||") == 0) {
			if (!logical_operator_expected || current_state != FILENAME) {
				printf("유효하지 않은 명령어입니다.\n");
				return 1;
			}
			current_state = (strcmp(token, "&&") == 0) ? AND_OPERATOR : OR_OPERATOR;
			logical_operator_expected = 0;
		} else {
			if (logical_operator_expected) {
				printf("유효하지 않은 명령어입니다.\n");
				return 1;
			}
			current_state = FILENAME;
			logical_operator_expected = 1;
		}

		token = strtok(NULL, " "); // 다음 토큰으로 이동
	}

	if (paren_count != 0 || !logical_operator_expected) {
		printf("유효하지 않은 명령어입니다.\n");
		return 1;
	}

	printf("유효한 명령어입니다.\n");
	return 0;
}
