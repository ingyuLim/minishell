/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:51:25 by seunan            #+#    #+#             */
/*   Updated: 2024/01/01 19:58:51 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_size(int n)
{
	size_t	size;

	if (n == 0)
		return (1);
	size = 0;
	while (n != 0)
	{
		n /= 10;
		++size;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char		*out;
	int			neg;
	long long	ncpy;
	int			i;

	ncpy = n;
	neg = 0;
	if (ncpy < 0)
	{
		ncpy *= -1;
		neg = 1;
	}
	out = ft_calloc(sizeof(char), (get_size(n) + neg + 1));
	if (!out)
		return (NULLPTR);
	i = get_size(n) + neg;
	while (--i >= 0)
	{
		out[i] = ncpy % 10 + '0';
		ncpy /= 10;
	}
	if (neg == 1)
		out[0] = '-';
	return (out);
}
