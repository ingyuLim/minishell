#include "../minishell.h"

int	b_env(t_list **lst, t_env *env)
{
	t_env	*tmp;
	t_list	*head;

	*lst = (*lst)->next;
	if (*lst == NULL)
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
	else
	{
		head = *lst;
		while (head != NULL && ft_isspecialtok(head->state) == 0)
		{
			tmp = env;
			while (tmp != NULL)
			{
				if (ft_strncmp(tmp->key, head->token, ft_strlen(tmp->key)) == 0)
				{
					if (head->token[ft_strlen(tmp->key)] == '=')
					{
						free(tmp->value);
						tmp->value = ft_strdup(head->token + ft_strlen(tmp->key) + 1);
					}
					break ;
				}
				tmp = tmp->next;
			}
			if (tmp == NULL)
				ft_envadd_back(&env, make_env(head->token));
			head = head->next;
		}
	}
	return (0);
}
