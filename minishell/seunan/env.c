#include "../minishell.h"

void	env(t_list *lst, char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	(void)lst;
}
