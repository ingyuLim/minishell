#include <unistd.h>
#include <fcntl.h>

int main()
{
	char buf[5];
	int fd = open("infile",O_RDONLY);
	read(fd,buf,5);
	write(1,buf,5);
}
