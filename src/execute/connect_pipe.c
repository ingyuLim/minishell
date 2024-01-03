/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:40:34 by seunan            #+#    #+#             */
/*   Updated: 2023/10/02 21:40:34 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_cmd(int (*pipe_fd)[2])
{
	use_close(pipe_fd[0][0]);
	change_stdout_to_pipe(pipe_fd[0]);
}

void	middle_cmd(int pid_index, int (*pipe_fd)[2])
{
	use_close(pipe_fd[pid_index - 1][1]);
	use_close(pipe_fd[pid_index][0]);
	change_stdin_to_pipe(pipe_fd[pid_index - 1]);
	change_stdout_to_pipe(pipe_fd[pid_index]);
}

void	last_cmd(int pid_index, int (*pipe_fd)[2])
{
	use_close(pipe_fd[pid_index - 1][1]);
	change_stdin_to_pipe(pipe_fd[pid_index - 1]);
}

void	connect_pipe(int pid_index, int process, int (*pipe_fd)[2])
{
	if (pid_index == 0 && pid_index == process - 1)
		;
	else if (pid_index == 0)
		first_cmd(pipe_fd);
	else if (pid_index != process - 1)
		middle_cmd(pid_index, pipe_fd);
	else
		last_cmd(pid_index, pipe_fd);
}
