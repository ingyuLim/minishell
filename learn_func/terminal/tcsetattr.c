/* tcsetattr 함수는 C 언어를 사용하여 터미널 속성을 설정하는 데 사용됩니다.
이 함수를 사용하면 터미널의 다양한 속성을 변경하고 제어할 수 있습니다. */

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

int main() {
	struct termios old_attr, new_attr;

	// Get the current terminal attributes
	if (tcgetattr(STDIN_FILENO, &old_attr) != 0) {
		perror("tcgetattr");
		exit(1);
	}

	// Copy the current attributes to the new attributes
	new_attr = old_attr;

	// Set the terminal to canonical (line-buffered) input mode
	new_attr.c_lflag |= ICANON;

	// Apply the new attributes to the terminal
	if (tcsetattr(STDIN_FILENO, TCSANOW, &new_attr) != 0) {
		perror("tcsetattr");
		exit(1);
	}

	// Restoring the original terminal attributes when done is recommended,
	// but not shown in this example. You should save 'old_attr' and restore it later.

	// Now you can read input with line buffering
	char buffer[256];
	printf("Enter something: ");
	fgets(buffer, sizeof(buffer), stdin);
	printf("You entered: %s\n", buffer);

	return 0;
}
