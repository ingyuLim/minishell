/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:02:15 by seunan            #+#    #+#             */
/*   Updated: 2024/01/03 12:39:00 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_unset(char **cmd, t_env **env)
{
	int		i;

	i = 1;
	while ((*env) != NULL && cmd[i] != NULL)
	{
		change_head(cmd[i], env);
		if ((*env) != NULL)
			delete_node(cmd[i], *env);
		++i;
	}
	return (0);
}

void	change_head(char *cmd, t_env **env)
{
	t_env	*tmp;

	if (*env == NULL)
		return ;
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
	t_env	*tmp;

	if (env == NULL)
		return ;
	while (env && env->next != NULL)
	{
		prev = env;
		env = env->next;
		if (ft_strncmp(env->key, cmd, ft_strlen(cmd) + 1) == 0)
		{
			use_free(env->key);
			use_free(env->value);
			env->key = NULL;
			env->value = NULL;
			tmp = env->next;
			use_free(env);
			env = tmp;
			prev->next = env;
		}
	}
}
