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
			use_free((*env)->key);
			use_free((*env)->value);
			(*env)->key = NULL;
			(*env)->value = NULL;
			tmp = (*env);
			(*env) = (*env)->next;
			use_free(tmp);
		}
		tmp = *env;
		while (tmp->next != NULL)
		{
			prev = tmp;
			tmp = tmp->next;
			if (ft_strncmp(tmp->key, cmd[i], ft_strlen(cmd[i]) + 1) == 0)
			{
				use_free(tmp->key);
				use_free(tmp->value);
				tmp->key = NULL;
				tmp->value = NULL;
				prev->next = tmp->next;
				use_free(tmp);
			}
		}
		++i;
	}
	return (0);
}
