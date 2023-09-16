// https://www.joinc.co.kr/w/man/3/getenv

#include <stdlib.h>
#include <stdio.h>

void	leak(void)
{
	system("leaks a.out > leaks_result_temp; cat leaks_result_temp | grep leaked && rm -rf leaks_result_temp");
}

int main(void)
{
	atexit(leak);
	char *value = getenv();
	printf("%s\n", value);

	return 0;
}
