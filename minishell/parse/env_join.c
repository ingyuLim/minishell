/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:13:31 by seunan            #+#    #+#             */
/*   Updated: 2023/09/27 14:20:24 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	state_join(char **result, int *i)
{
	char	*tmp;

	tmp = *result;
	*result = ft_strjoin(*result, ft_itoa(g_status));
	use_free(tmp);
	*i += 2;
}

void	env_join(char *content, char **result, int *i, t_env *env)
{
	int		j;
	char	*tmp;
	char	*key;

	j = *i + 1;
	while (content[j] != '\0'
		&& !ft_iswhitespace(content[j])
		&& !ft_isquote(content[j])
		&& content[j] != '$'
		&& content[j] != '=')
		j++;
	key = ft_substr(content, *i + 1, j - *i - 1);
	tmp = *result;
	*result = ft_strjoin(*result, find_env(key, env));
	use_free(tmp);
	use_free(key);
	*i = j;
}

char	*ft_strjoin_char(char *s1, char c)
{
	char	*result;
	int		i;

	result = ft_calloc(ft_strlen(s1) + 2, sizeof(char));
	i = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		++i;
	}
	result[i] = c;
	use_free(s1);
	return (result);
}
