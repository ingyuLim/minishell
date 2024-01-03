/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:08:57 by seunan            #+#    #+#             */
/*   Updated: 2024/01/01 19:58:35 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*out;
	size_t	i;

	out = ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	if (!out)
		return (NULLPTR);
	i = 0;
	while (s1[i] != '\0')
	{
		out[i] = s1[i];
		++i;
	}
	return (out);
}
