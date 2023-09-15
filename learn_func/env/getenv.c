// https://www.joinc.co.kr/w/man/3/getenv

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	(void) argc;
	char *value;
	value = getenv(argv[1]);

	if (value != NULL)
		printf("%s=%s\n", argv[1], value);

	return 0;
}
