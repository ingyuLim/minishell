/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:51:25 by seunan            #+#    #+#             */
/*   Updated: 2023/08/21 21:33:01 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	is_size(int n)
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
	char		*num;
	int			minus;
	long long	ncpy;
	int			i;

	ncpy = n;
	minus = 0;
	if (ncpy < 0)
	{
		ncpy *= -1;
		++minus;
	}
	num = ft_calloc(sizeof(char), (is_size(n) + minus + 1));
	if (!num)
		return (0);
	i = is_size(n) + minus;
	while (--i >= 0)
	{
		num[i] = ncpy % 10 + '0';
		ncpy /= 10;
	}
	if (minus == 1)
		num[0] = '-';
	return (num);
}
