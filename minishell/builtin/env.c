#include "../minishell.h"

void	print_env(t_env *env)
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

void	add_env(t_env *env, char *cmd)
{
	t_env	*e_tmp;

	e_tmp = env;
	while (e_tmp != NULL)
	{
		if (ft_strncmp(e_tmp->key, cmd, ft_strlen(e_tmp->key)) == 0)
		{
			if (cmd[ft_strlen(e_tmp->key)] == '=')
			{
				use_free(e_tmp->value);
				e_tmp->value = ft_strdup(cmd + ft_strlen(e_tmp->key) + 1);
				break ;
			}
			else if (cmd[ft_strlen(e_tmp->key)] == '\0')
				break ;
		}
		e_tmp = e_tmp->next;
	}
	if (e_tmp == NULL)
	{
		if (!ft_isvalidkey(cmd))
			printf("minishell: export: `%s': not a valid identifier\n", cmd);
		else
			ft_envadd_back(&env, make_env(cmd));
	}
}

int	b_env(char **cmd, t_env *env)
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
