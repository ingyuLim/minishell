/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:01:58 by seunan            #+#    #+#             */
/*   Updated: 2023/10/09 03:54:43 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	b_exit(char **cmd)
{
	int	i;

	i = 0;
	if (cmd[1] == NULL)
		exit(0);
	if (!is_num(cmd[1]))
	{
		error_msg("numeric argument required", "exit", cmd[1]);
		return (255);
	}
	while (cmd[i] != NULL)
		++i;
	if (i > 2)
	{
		error_msg("too many arguments", "exit", 0);
		return (1);
	}
	exit(ft_atoi(cmd[1]));
}

int	is_num(char *str)
{
	int				i;
	long long int	num;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		++i;
	num = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		num = num * 10 + str[i] - '0';
		if (num >= __LONG_LONG_MAX__ / 10
			&& ft_isdigit(str[i + 1]) && str[i + 1] > '7')
			return (0);
		++i;
	}
	return (1);
}
