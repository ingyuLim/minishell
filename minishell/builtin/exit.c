#include "../minishell.h"

int	b_exit(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
		++i;
	if (i > 2)
	{
		error("too many arguments");
		return (1);
	}
	if (cmd[1] == NULL)
		exit(0);
	exit(ft_atoi(cmd[1]));
}
