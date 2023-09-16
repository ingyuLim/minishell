// https://recipes4dev.tistory.com/171

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	// execve("/usr/bin/awk", (char *[]){"awk", "{print}", "./file.txt", NULL}, NULL);
	execve("/usr/bin/awk", (char *[]){"awk", "BEGIN { print \"TITLE : Field value 1,2\"} {print $1, $2} END {print \"Finished\"}", "./file.txt", NULL}, NULL);
	perror("execve");

	return (0);
}
