// https://www.joinc.co.kr/w/man/2/ttyname

#include <unistd.h>

#include <stdio.h>
int main()
{
	printf("Your tty name is : %s\n", ttyname(0));
}
