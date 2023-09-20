#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int fd = open("abc", O_WRONLY | O_CREAT, 0644);
	dup2(fd, 1);
	dup2(2, fd);
	write(fd, "dasd", 5);
	return 0;
}
