#include "../minishell.h"

int	b_export(char **cmd, t_env *env)
{
	int		i;

	if (cmd[1] == NULL)
		print_env(env);
	else
	{
		i = 1;
		while (cmd[i] != NULL)
		{
			add_env(env, cmd[i]);
			++i;
		}
	}
	return (0);
}
