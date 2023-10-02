/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_in_and_out.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:39:58 by seunan            #+#    #+#             */
/*   Updated: 2023/10/02 21:39:59 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_stdin_to_pipe(int *pipe_fd)
{
	use_dup2(pipe_fd[0], STDIN_FILENO);
	use_close(pipe_fd[0]);
}

void	change_stdout_to_pipe(int *pipe_fd)
{
	use_dup2(pipe_fd[1], STDOUT_FILENO);
	use_close(pipe_fd[1]);
}
