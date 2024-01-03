/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 20:18:42 by seunan            #+#    #+#             */
/*   Updated: 2024/01/03 12:35:26 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

int	ft_is_redirection(t_list *lst)
{
	while (lst != NULL && lst->state != PIPE)
	{
		if (lst->state == IN_REDIR || lst->state == OUT_REDIR
			|| lst->state == HEREDOC || lst->state == PAIR_OUT_REDIR)
			return (1);
		lst = lst->next;
	}
	return (0);
}

void	clear_resources(char **envp, int process, int (*pipe_fd)[2],
		char **tmp_arr)
{
	free_envp(envp);
	if (process > 1)
		use_free(pipe_fd);
	if (tmp_arr != NULL)
		free_tmp_arr(tmp_arr);
}

void	close_last_pipe(int (*pipe_fd)[2], int pid_index)
{
	close(pipe_fd[pid_index - 1][0]);
	close(pipe_fd[pid_index - 1][1]);
}

char	**parse_path(t_env *env)
{
	char	**path;

	while (env != NULL)
	{
		if (ft_strncmp(env->key, "PATH", 5) == 0)
		{
			path = ft_split(env->value, ':', '/');
			return (path);
		}
		env = env->next;
	}
	return (NULL);
}

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i] != NULL)
	{
		use_free(path[i]);
		i++;
	}
	use_free(path);
}
