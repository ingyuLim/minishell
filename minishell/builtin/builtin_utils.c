#include "../minishell.h"

int	ft_isspecialtok(t_state state)
{
	if (state == PIPE)
		return (1);
	else if (state == IN_REDIR)
		return (1);
	else if (state == OUT_REDIR)
		return (1);
	else if (state == HEREDOC)
		return (1);
	else if (state == PAIR_OUT_REDIR)
		return (1);
	return (0);
}

t_env	*ft_envlast(t_env *env)
{
	if (env == NULL)
		return (NULL);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

void	ft_envadd_back(t_env **head, t_env *new)
{
	t_env	*tmp;

	if (new == NULL)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	tmp = ft_envlast(tmp);
	tmp->next = new;
}

int	ft_isvalidid(char *content)
{
	int	i;

	if (!ft_isalpha(content[0]) && content[0] != '_')
		return (0);
	i = 0;
	while (content[i] != '\0')
	{
		if (!ft_isalnum(content[i]) && content[i] != '_')
			return (0);
		++i;
	}
	return (1);
}

t_env	*make_env(char *contents)
{
	t_env	*env;
	char	*tmp;
	char	*cut;

	// if (ft_isvalidid(contents) == 0)
	// {
	// 	error("not a valid identifier");
	// 	return (NULL);
	// }
	tmp = ft_strdup(contents);
	env = (t_env *)ft_calloc(1, sizeof(t_env));
	cut = ft_strchr(tmp, '=');
	if (cut == NULL)
	{
		env->key = tmp;
		env->value = NULL;
		return (env);
	}
	env->value = ft_strdup(cut + 1);
	*cut = '\0';
	env->key = ft_strdup(tmp);
	env->next = NULL;
	free(tmp);
	return (env);
}

t_env	*dup_env(char *envp[])
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		ft_envadd_back(&env, make_env(envp[i]));
		++i;
	}
	return (env);
}
