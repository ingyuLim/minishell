/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:29:19 by seunan            #+#    #+#             */
/*   Updated: 2023/08/21 21:34:00 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (ft_strlen(s) < start)
	{
		str = ft_calloc(1, 1);
		return (str);
	}
	else if (len > ft_strlen(s) - start)
		str = ft_calloc( ft_strlen(s) - start + 1, sizeof(char));
	else
		str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (0);
	i = 0;
	while (s[start] != '\0' && i < len && start < ft_strlen(s))
	{
		str[i] = s[start];
		++i;
		++start;
	}
	return (str);
}
