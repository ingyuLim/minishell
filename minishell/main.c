/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 22:42:16 by seunan            #+#    #+#             */
/*   Updated: 2023/08/28 02:41:07 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*str;

	while (1)
	{
		str = readline("\033[0;37mminishell$\033[0;31m>\033[0;m ");
		if (ft_strncmp(str, "exit", 5) == 0)
			break ;
		split_by_pipe(str);
		add_history(str);
		free(str);
	}
	return (0);
}
