/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 01:21:23 by seunan            #+#    #+#             */
/*   Updated: 2023/08/25 02:33:02 by seunan           ###   ########.fr       */
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
			if (str[i] == '\'' && (str[i + 1] == '|' || str[i + 1] == ' ' || str[i + 1] == '\0'))
				++sin;
		++i;
	}
	printf("%s\n", answer);
}
