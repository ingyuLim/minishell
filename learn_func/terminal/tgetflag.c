// gcc tgetflag.c -lncurses -o tgetflag

#include <stdio.h>
#include <stdlib.h>
#include <term.h>
#include <termios.h>
#include <unistd.h>
#include <curses.h>

int main() {
	char	term_buffer[1024];
	bool	has_auto_left_margin, has_auto_right_margin;

	// Initialize curses
	initscr();

	// Use tgetent to retrieve terminal information
	if (tgetent(term_buffer, getenv("TERM")) != 1) {
		fprintf(stderr, "Error: Unable to retrieve terminal information\n");
		endwin(); // End curses mode
		return 1;
	}

	// Use tgetflag to check specific terminal flags
	has_auto_left_margin = tgetflag("am");
	has_auto_right_margin = tgetflag("mir");

	// Print the retrieved flags
	printf("Terminal Flags:\n");
	printf("Auto Left Margin: %s\n", has_auto_left_margin ? "Yes" : "No");
	printf("Auto Right Margin: %s\n", has_auto_right_margin ? "Yes" : "No");

	// End curses mode
	endwin();

	return 0;
}
