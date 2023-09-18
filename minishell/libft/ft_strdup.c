/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:08:57 by seunan            #+#    #+#             */
/*   Updated: 2023/09/17 18:58:10 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*answer;
	size_t	i;

	answer = ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	i = 0;
	while (s1[i] != '\0')
	{
		answer[i] = s1[i];
		++i;
	}
	return (answer);
}
