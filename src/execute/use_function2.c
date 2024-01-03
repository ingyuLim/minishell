/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_function2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:39:35 by seunan            #+#    #+#             */
/*   Updated: 2024/01/03 12:36:31 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "minishell.h"

pid_t	use_waitpid(pid_t pid, int *stat_loc, int options)
{
	pid_t	result;

	result = waitpid(pid, stat_loc, options);
	if (result == -1)
		exit_with_err("waitpid", 0, 1);
	return (result);
}

void	use_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		exit_with_err("dup2", 0, 1);
}

void	use_close(int fd)
{
	if (close(fd) == -1)
		exit_with_err("close", 0, 1);
}

int	infile_open(const char *path, int oflag)
{
	int	fd;

	fd = open(path, oflag);
	if (fd == -1)
		exit_with_err("open", 0, 1);
	return (fd);
}

void	free_tmp_arr(char **tmp_arr)
{
	int	i;

	i = 0;
	while (tmp_arr[i] != NULL)
	{
		use_free(tmp_arr[i]);
		i++;
	}
	use_free(tmp_arr);
}
