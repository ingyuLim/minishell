/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anseungwon <anseungwon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:08:57 by seunan            #+#    #+#             */
/*   Updated: 2023/07/18 11:11:47 by anseungwon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*answer;
	size_t	i;

	answer = ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	if (!answer)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		answer[i] = s1[i];
		++i;
	}
	return (answer);
}
