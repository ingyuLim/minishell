#include "../minishell.h"

int	b_export(char **cmd, t_env *env)
{
	int		i;

	if (cmd[1] == NULL)
		print_env(env, 1);
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
			error_msg("not a valid identifier", "export", cmd);
		else
			ft_envadd_back(&env, make_env(cmd));
	}
}

void	print_env(t_env *env, int flag)
{
	while (env != NULL)
	{
		if (flag == 1)
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env->key, STDOUT_FILENO);
		if (env->value != NULL)
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			if (flag == 1)
				ft_putstr_fd("\"", STDOUT_FILENO);
			ft_putstr_fd(env->value, STDOUT_FILENO);
			if (flag == 1)
				ft_putchar_fd('\"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		env = env->next;
	}
}
