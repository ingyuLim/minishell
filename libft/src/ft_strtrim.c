/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 21:28:18 by seunan            #+#    #+#             */
/*   Updated: 2024/01/01 19:58:47 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_bool	is_set(char c, char const *set)
{
	while (*set != '\0')
	{
		if (*set == c)
			return (TRUE);
		++set;
	}
	return (FALSE);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	end;
	size_t	i;

	start = 0;
	while (is_set(s1[start], set))
		++start;
	end = ft_strlen(s1);
	while (is_set(s1[end - 1], set))
		--end;
	if (start >= end)
	{
		str = ft_calloc(1, 1);
		return (str);
	}
	str = ft_calloc(1, (end - start + 1));
	if (!str)
		return (NULLPTR);
	i = 0;
	while (start < end)
		str[i++] = s1[start++];
	return (str);
}
