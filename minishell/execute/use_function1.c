/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_function1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:39:38 by seunan            #+#    #+#             */
/*   Updated: 2023/10/03 02:41:59 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	use_execve(char *path, char *argv[], char *envp[])
{
	g_status = 0;
	if (execve(path, argv, envp) == -1)
	{
		if (access(path, F_OK) == 0 && ft_strchr(path, '/'))
			g_status = 126;
		else
			g_status = 127;
		exit_with_err(path, 0, g_status);
	}
}

void	use_pipe(int *fd)
{
	if (pipe(fd) == -1)
		exit_with_err("pipe", 0, 1);
}

pid_t	use_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_with_err("fork", 0, 1);
	return (pid);
}

void	use_free(void *mem)
{
	ft_bzero((char *)mem, ft_strlen(mem));
	free(mem);
}
