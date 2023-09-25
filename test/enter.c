#include "../minishell/minishell.h"

int main(void)
{
	char buf[1];
	write(1,"> ",2);
	while(read(0,buf,1))
	{
		write(1,buf,1);
		if (*buf == '\n')
			write(1,"> ",2);
	}
}
