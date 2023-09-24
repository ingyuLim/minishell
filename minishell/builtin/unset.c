#include "../minishell.h"

int	b_unset(char **cmd, t_env **env)
{
	int		i;
	t_env	*prev;
	t_env	*tmp;

	i = 1;
	while (cmd[i] != NULL)
	{
		if (ft_strncmp((*env)->key, cmd[i], ft_strlen(cmd[i]) + 1) == 0)
		{
			free((*env)->key);
			free((*env)->value);
			(*env)->key = NULL;
			(*env)->value = NULL;
			tmp = (*env);
			(*env) = (*env)->next;
			free(tmp);
		}
		tmp = *env;
		while (tmp->next != NULL)
		{
			prev = tmp;
			tmp = tmp->next;
			if (ft_strncmp(tmp->key, cmd[i], ft_strlen(cmd[i]) + 1) == 0)
			{
				free(tmp->key);
				free(tmp->value);
				tmp->key = NULL;
				tmp->value = NULL;
				prev->next = tmp->next;
				free(tmp);
			}
		}
		++i;
	}
	return (0);
}
