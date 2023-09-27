/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:02:04 by seunan            #+#    #+#             */
/*   Updated: 2023/09/27 14:02:20 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	b_cd(char **cmd)
{
	char	*path;

	if (cmd[1] == NULL || ft_strncmp(cmd[1], "~", 2) == 0)
		path = getenv("HOME");
	else
		path = cmd[1];
	if (chdir(path) == -1)
	{
		error(path, "cd");
		return (1);
	}
	return (0);
}
