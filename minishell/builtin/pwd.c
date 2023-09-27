/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:02:13 by seunan            #+#    #+#             */
/*   Updated: 2023/09/27 14:02:14 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	b_pwd(void)
{
	char	*path;

	path = getcwd(NULL, BUFSIZ);
	ft_putendl_fd(path, STDOUT_FILENO);
	use_free(path);
	return (0);
}
