/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:01:09 by seunan            #+#    #+#             */
/*   Updated: 2023/10/09 03:57:46 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_envvar(char *content, int i)
{
	if (content[i] == '$'
		&& (content[i + 1] == '?'
			|| content[i + 1] == '_'
			|| ft_isalpha(content[i + 1])))
		return (1);
	return (0);
}

int	is_state(char *content, int i)
{
	if (content[i + 1] == '?')
		return (1);
	return (0);
}

int	is_valid_quotes(char *str)
{
	int	i;
	int	sin;
	int	dou;

	i = 0;
	sin = 0;
	dou = 0;
	while (str[i])
	{
		if (str[i] == '\'' && dou % 2 == 0)
			sin++;
		else if (str[i] == '\"' && sin % 2 == 0)
			dou++;
		i++;
	}
	if (sin % 2 == 0 && dou % 2 == 0)
		return (1);
	return (0);
}

char	*find_env(char *key, t_env *env)
{
	while (env != NULL)
	{
		if (ft_strncmp(key, env->key, ft_strlen(key) + 1) == 0)
			return (env->value);
		env = env->next;
	}
	return ("");
}

int	quotes_check(char *str)
{
	if (is_valid_quotes(str) == 0)
	{
		use_free(str);
		g_status = 2;
		error_msg("Invalid quotes", 0, 0);
		return (0);
	}
	return (1);
}
