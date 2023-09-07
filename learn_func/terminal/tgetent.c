// gcc tgetent.c -lncurses -o tgetent

#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <term.h>
#include <termios.h>
#include <unistd.h>

int main() {
	char term_buffer[1024];

	// Initialize curses
	initscr();

	// Use tgetent to retrieve terminal information
	if (tgetent(term_buffer, getenv("TERM")) != 1) {
		fprintf(stderr, "Error: Unable to retrieve terminal information\n");
		endwin(); // End curses mode
		return 1;
	}

	// Retrieve and print the terminal name
	char* term_name = getenv("TERM");
	printf("Terminal Name: %s\n", term_name);
	// End curses mode
	endwin();

	return 0;
}
