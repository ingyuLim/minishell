#include "../minishell.h"

void	change_head(char *cmd, t_env **env)
{
	t_env	*tmp;

	if (ft_strncmp((*env)->key, cmd, ft_strlen(cmd) + 1) == 0)
	{
		use_free((*env)->key);
		use_free((*env)->value);
		(*env)->key = NULL;
		(*env)->value = NULL;
		tmp = (*env);
		(*env) = (*env)->next;
		use_free(tmp);
	}
}

void	delete_node(char *cmd, t_env *env)
{
	t_env	*prev;

	while (env->next != NULL)
	{
		prev = env;
		env = env->next;
		if (ft_strncmp(env->key, cmd, ft_strlen(cmd) + 1) == 0)
		{
			use_free(env->key);
			use_free(env->value);
			env->key = NULL;
			env->value = NULL;
			prev->next = env->next;
			use_free(env);
		}
	}
}

int	b_unset(char **cmd, t_env **env)
{
	int		i;

	i = 1;
	while (cmd[i] != NULL)
	{
		change_head(cmd[i], env);
		delete_node(cmd[i], *env);
		++i;
	}
	return (0);
}
