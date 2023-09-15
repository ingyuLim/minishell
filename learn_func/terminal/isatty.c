// https://www.joinc.co.kr/w/man/3/isatty

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main()
{
	int fd;
	// 표준입력은 터미널에 연결되어 있으므로 1을 출력한다.
	printf("%d\n", isatty(0));

	// 파일은 터미널에 연결되어 있지 않으므로 0을 출력한다.
	fd = open("test100", O_RDWR);
	printf("%d\n", isatty(fd));
	close(fd);

	fd = open("/dev/ttyS0", O_RDONLY);
	if (fd < -1)
	{
		printf("open error\n");
		exit(0);
	}
	printf("%d\n", isatty(fd));
	close(fd);
	exit(0);
}
