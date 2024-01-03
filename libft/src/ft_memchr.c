/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anseungwon <anseungwon@student.42seoul.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:34:04 by seunan            #+#    #+#             */
/*   Updated: 2023/03/19 19:33:19 by anseungwon       ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((void *)s);
		++s;
	}
	return (0);
}
