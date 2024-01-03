/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:07:40 by seunan            #+#    #+#             */
/*   Updated: 2024/01/01 19:58:28 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	tmp;

	if (*needle == '\0')
		return ((char *) haystack);
	i = 0;
	while (haystack[i] != '\0' && i < len)
	{
		if (haystack[i] == needle[0])
		{
			tmp = i;
			j = 0;
			while (haystack[tmp] != '\0' && tmp < len
				&& haystack[tmp] == needle[j])
			{
				++tmp;
				++j;
			}
			if (needle[j] == '\0')
				return ((char *)(haystack + i));
		}
		++i;
	}
	return (NULLPTR);
}
