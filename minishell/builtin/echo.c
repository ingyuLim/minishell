#include "../minishell.h"

int	b_echo(char **cmd)
{
	int	flag;
	int	i;

	flag = 0;
	i = 1;
	if(cmd[1] != NULL && ft_strncmp("-n", cmd[1], 3) == 0)
	{
		flag = 1;
		i = 2;
	}
	while(cmd[i] != NULL)
	{
		ft_putstr_fd(cmd[i], 1);
		if(cmd[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		++i;
	}
	if(flag == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
