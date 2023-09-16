#include <unistd.h>

void	unset(char *argv[], char *env[])
{
	//1.'=' 문자가 있으면 perror찍기. 하지만 즉시 return은 아니고 에러 메시지만.
	//2. 아 이거 envp 리스트로 들고 다녀야겠는데.
	int	size;

	size = 1;
	while(env[size - 1] != NULL)
		size++;
	
}