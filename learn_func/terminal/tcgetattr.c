/* tcgetattr 함수를 사용하여 현재 터미널 속성을 가져오는 예제를 제공하겠습니다.
이 코드는 현재 터미널의 속성을 검색하고, 그 정보를 출력합니다. */

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

int main() {
	struct termios term_attr;

	// Get the current terminal attributes
	if (tcgetattr(STDIN_FILENO, &term_attr) != 0) {
		perror("tcgetattr");
		exit(1);
	}

	// Print the retrieved terminal attributes
	printf("Terminal attributes:\n");
	printf("c_iflag: 0x%08lx\n", term_attr.c_iflag);
	printf("c_oflag: 0x%08lx\n", term_attr.c_oflag);
	printf("c_cflag: 0x%08lx\n", term_attr.c_cflag);
	printf("c_lflag: 0x%08lx\n", term_attr.c_lflag);

	return 0;
}
