#include "../minishell.h"

int	b_unset(t_list **lst, t_env **env)
{
	t_env	*prev;
	t_env	*tmp;

	*lst = (*lst)->next;
	while (*lst != NULL && ft_isspecialtok((*lst)->state) == 0)
	{
		if (ft_strncmp((*env)->key, (*lst)->token, ft_strlen((*lst)->token) + 1) == 0)
		{
			free((*env)->key);
			free((*env)->value);
			(*env)->key = NULL;
			(*env)->value = NULL;
			tmp = (*env);
			(*env) = (*env)->next;
			free(tmp);
			printf("head key: %s\n", (*env)->key);
		}
		tmp = *env;
		while (tmp->next != NULL)
		{
			prev = tmp;
			tmp = tmp->next;
			if (ft_strncmp(tmp->key, (*lst)->token, ft_strlen((*lst)->token) + 1) == 0)
			{
				free(tmp->key);
				free(tmp->value);
				tmp->key = NULL;
				tmp->value = NULL;
				prev->next = tmp->next;
				free(tmp);
			}
		}
		*lst = (*lst)->next;
	}
	return (0);
}
