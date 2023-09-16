#include <unistd.h>
#include "../minishell/libft/libft.h"
void	mini_exit(char *argv[])
{
	int argc;

	argc = 1;
	while(argv[argc] != NULL)
		argc++;
	if(argc > 2)
		printf("exit: too many arguments\n");
	else
		exit(ft_atoi(argv[1]));
}