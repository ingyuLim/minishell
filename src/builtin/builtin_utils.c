/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:02:01 by seunan            #+#    #+#             */
/*   Updated: 2024/01/03 12:36:36 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isvalidkey(char *key)
{
	int	i;

	if (!ft_isalpha(*key) && *key != '_')
		return (0);
	i = 0;
	while (key[i] != '=' && key[i] != '\0')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
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

t_env	*make_env(char *content)
{
	t_env	*env;
	char	*tmp;
	char	*cut;

	tmp = ft_strdup(content);
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
	use_free(tmp);
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
