#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	open("tmp 2639", O_WRONLY | O_CREAT, 0644);
	return 0;
}
