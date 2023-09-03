/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inlim <inlim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 01:21:23 by seunan            #+#    #+#             */
/*   Updated: 2023/08/25 02:12:41 by inlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 1. 따옴표를 찾는다.
// 2.

#include "minishell.h"

void	pair_quotes(char *str)
{
	int	i, j;
	int sin = 0, dou = 0;
	int	len = ft_strlen(str);
	char	*answer = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && dou == 0 && sin == 0)
			++sin;
		if (str[i] == '\"' && dou == 0 && sin == 0)
			++dou;
		if (sin == 1)
		{
			for (j = len - 1; j > i; j--)
			{
				if (str[j] == '\'')
					++sin;
				if (sin == 2)
				{
					printf("%d\n",j-i);
					answer = ft_calloc(j - i + 1, sizeof(char));
					break;
				}
			}
			for (int k = i; i <= j; k++)
			{
				if (str[i] == '\'')
				{
					++i;
					continue;
				}
				answer[k] = str[i];
				++i;
			}
			break;
		}
		++i;
	}
	printf("%s\n", answer);
}
