#include "../minishell.h"

// export a : declare -x a
// => key: a, value: NULL

// export a= : declare -x a=""
// => key: a, value: '\0'

// export a=b : declare -x a="b"
// => key: a, value: b

int	b_export(t_list **lst, t_env *env)
{
	t_env	*e_tmp;
	t_list	*l_tmp;

	*lst = (*lst)->next;
	if (*lst == NULL || ft_isspecialtok((*lst)->state))	// export, export | ... , export [REDIRECTION] ...
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
		l_tmp = *lst;
		while (l_tmp != NULL && ft_isspecialtok(l_tmp->state) == 0)
		{
			e_tmp = env;
			while (e_tmp != NULL)
			{
				if (ft_strncmp(e_tmp->key, l_tmp->token, ft_strlen(e_tmp->key)) == 0)
				{
					if (l_tmp->token[ft_strlen(e_tmp->key)] == '=')
					{
						free(e_tmp->value);
						e_tmp->value = ft_strdup(l_tmp->token + ft_strlen(e_tmp->key) + 1);
						break ;
					}
					else if (l_tmp->token[ft_strlen(e_tmp->key)] == '\0')
						break ;
				}
				e_tmp = e_tmp->next;
			}
			if (e_tmp == NULL)
			{
				if (!ft_isvalidkey(l_tmp->token))
					printf("minishell: export: `%s': not a valid identifier\n", l_tmp->token);
				else
					ft_envadd_back(&env, make_env(l_tmp->token));
			}
			l_tmp = l_tmp->next;
		}
	}
	return (0);
}
