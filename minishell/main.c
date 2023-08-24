/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 22:42:16 by seunan            #+#    #+#             */
/*   Updated: 2023/08/24 23:11:32 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char *str;
	while(1)
	{
		str = readline("minishell $>");
		if (strcmp(str, "exit") == 0)
		{
			printf("exit ...\n");
			break;
		}
		else
			printf("Result : %s\n\n", str);
		add_history(str);
		free(str);
	}
	return (0);
}
