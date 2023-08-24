/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 22:42:16 by seunan            #+#    #+#             */
/*   Updated: 2023/08/25 01:54:13 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char *str;
	while(1)
	{
		str = readline("minishell $>");
		if (ft_strncmp(str, "exit", 5) == 0)
		{
			printf("exit");
			break;
		}
		else
		{
			pair_quotes(str);
		}
		add_history(str);
		free(str);
	}
	return (0);
}
