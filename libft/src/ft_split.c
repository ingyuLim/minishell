/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:19:23 by seunan            #+#    #+#             */
/*   Updated: 2024/01/03 12:39:32 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	**str_free(char **answer, int arridx)
{
	int	i;

	i = 0;
	while (i <= arridx)
	{
		free(answer[i]);
		++i;
	}
	free(answer);
	return (0);
}

static int	cnt_strnum(char const *s, char c)
{
	int	strnum;
	int	i;

	strnum = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if ((s[i] != c) && ((s[i + 1] == c) || s[i + 1] == '\0'))
			++strnum;
		++i;
	}
	return (strnum);
}

static char	*str_maker(const char *s, int *sidx, char c, char suffix)
{
	char	*str;
	int		strlen;

	strlen = 0;
	while (s[*sidx] == c)
		++*sidx;
	while (s[*sidx] != '\0' && s[*sidx] != c)
	{
		++strlen;
		++*sidx;
	}
	str = (char *) ft_calloc(sizeof(char), (strlen + 1 + (suffix != '\0')));
	*sidx -= strlen;
	strlen = 0;
	while (s[*sidx] != '\0' && s[*sidx] != c)
	{
		str[strlen] = s[*sidx];
		++*sidx;
		++strlen;
	}
	str[strlen] = suffix;
	return (str);
}

char	**ft_split(char const *s, char c, char suffix)
{
	char	**answer;
	char	*str;
	int		i;
	int		strnum;
	int		sidx;

	strnum = cnt_strnum(s, c);
	answer = (char **)ft_calloc(sizeof(char *), (strnum + 1));
	i = 0;
	sidx = 0;
	while (i < strnum)
	{
		str = str_maker(s, &sidx, c, suffix);
		if (!str)
			return (str_free(answer, i));
		answer[i] = str;
		++i;
	}
	return (answer);
}
