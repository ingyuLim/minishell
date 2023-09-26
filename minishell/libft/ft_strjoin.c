/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 21:07:32 by seunan            #+#    #+#             */
/*   Updated: 2023/09/26 23:58:45 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*answer;
	size_t	i;
	size_t	j;

	answer = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	i = 0;
	j = 0;
	while (s1 && s1[j] != '\0')
		answer[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j] != '\0')
		answer[i++] = s2[j++];
	return (answer);
}
