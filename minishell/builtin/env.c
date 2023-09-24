#include "../minishell.h"

int	b_env(char **cmd, t_env *env)
{
	t_env	*e_tmp;
	int		i;

	if (cmd[1] == NULL)	// export, export | ... , export [REDIRECTION] ...
	{
		while (env != NULL)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(env->key, STDOUT_FILENO);
			if (env->value != NULL)
			{
				ft_putstr_fd("=\"", STDOUT_FILENO);
				ft_putstr_fd(env->value, STDOUT_FILENO);
				ft_putchar_fd('\"', STDOUT_FILENO);
			}
			ft_putchar_fd('\n', STDOUT_FILENO);
			env = env->next;
		}
	}
	else // export [NAME[=VALUE]] ...
	{
		i = 1;
		while (cmd[i] != NULL)
		{
			e_tmp = env;
			while (e_tmp != NULL)
			{
				if (ft_strncmp(e_tmp->key, cmd[i], ft_strlen(e_tmp->key)) == 0)
				{
					if (cmd[i][ft_strlen(e_tmp->key)] == '=')
					{
						use_free(e_tmp->value);
						e_tmp->value = ft_strdup(cmd[i] + ft_strlen(e_tmp->key) + 1);
						break ;
					}
					else if (cmd[i][ft_strlen(e_tmp->key)] == '\0')
						break ;
				}
				e_tmp = e_tmp->next;
			}
			if (e_tmp == NULL)
			{
				if (!ft_isvalidkey(cmd[i]))
					printf("minishell: export: `%s': not a valid identifier\n", cmd[i]);
				else
					ft_envadd_back(&env, make_env(cmd[i]));
			}
			++i;
		}
	}
	return (0);
}
