/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:01:13 by seunan            #+#    #+#             */
/*   Updated: 2023/09/27 14:20:02 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_env_and_trim_quote(t_vars *vars)
{
	t_list	*lst;
	char	*mem;

	lst = vars->lst;
	while (lst != NULL)
	{
		mem = lst->token;
		lst->token = replace_env_vars(lst->token, vars->env);
		free(mem);
		lst = lst->next;
	}
}

char	*replace_env_vars(char *content, t_env *env)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (content[i] != '\0')
	{
		if (content[i] == '\'')
			meet_single_quote(&result, content, &i);
		else if (content[i] == '\"')
			meet_double_quote(&result, content, &i, env);
		else if (is_envvar(content, i))
		{
			if (is_state(content, i))
				state_join(&result, &i);
			else
				env_join(content, &result, &i, env);
		}
		else
		{
			result = ft_strjoin_char(result, content[i]);
			++i;
		}
	}
	return (result);
}

void	meet_single_quote(char **result, char *content, int *i)
{
	char	*tmp;
	char	*mem;
	int		start;
	int		len;

	++(*i);
	start = *i;
	len = 0;
	while (content[*i] != '\0' && content[*i] != '\'')
	{
		++len;
		++(*i);
	}
	++(*i);
	tmp = ft_substr(content, start, len);
	mem = *result;
	*result = ft_strjoin(*result, tmp);
	use_free(mem);
	use_free(tmp);
}

void	meet_double_quote(char **result, char *content, int *i, t_env *env)
{
	++(*i);
	while (content[*i] != '\0' && content[*i] != '\"')
	{
		if (is_envvar(content, *i))
		{
			if (is_state(content, *i))
				state_join(result, i);
			else
				env_join(content, result, i, env);
		}
		else
		{
			*result = ft_strjoin_char(*result, content[*i]);
			++(*i);
		}
	}
	++(*i);
}
