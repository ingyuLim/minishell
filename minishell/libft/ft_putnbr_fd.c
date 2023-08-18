/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:21:05 by seunan            #+#    #+#             */
/*   Updated: 2023/03/20 17:43:29 by seunan           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	write_num(int n, int fd)
{
	char	num;

	if (n == 0)
		return ;
	num = n % 10 + '0';
	write_num(n / 10, fd);
	write(fd, &num, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	tmp;

	if (n > 0)
		write_num(n, fd);
	else if (n == 0)
		write(fd, "0", 1);
	else
	{
		tmp = -1 * (n % 10) + '0';
		n /= 10;
		write(fd, "-", 1);
		write_num(n * -1, fd);
		write(fd, &tmp, 1);
	}
}
