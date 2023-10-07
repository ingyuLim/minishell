/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 20:18:39 by seunan            #+#    #+#             */
/*   Updated: 2023/10/07 16:21:27 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_frame(t_vars *vars)
{
	int		process;
	pid_t	*pid;
	int		(*pipe_fd)[2];

	signal(SIGINT, sigint_handler_exec);
	signal(SIGQUIT, sigquit_handler_exec);
	replace_env_and_trim_quote(vars);
	while (*(vars->lst->token) == '\0')
		vars->lst = vars->lst->next;
	process = process_count(vars->lst);
	pipe_fd = NULL;
	pid = ft_calloc(process, sizeof(pid_t));
	if (process > 1)
		pipe_fd = ft_calloc(process - 1, sizeof(int) * 2);
	execute(vars, pid, pipe_fd, process);
	wait_child(pid, process);
	use_free(pid);
}

void	execute(t_vars *vars, pid_t *pid, int (*pipe_fd)[2], int process)
{
	t_list		*lst;
	t_execute	data;

	init_variable(vars, &lst, &data);
	while (process > data.pid_index)
	{
		data.cmd = make_cmd(lst);
		if (data.pid_index != process - 1)
			pipe(pipe_fd[data.pid_index]);
		if (ft_onlybuiltin(data, lst, process))
			builtin_func(vars, data.cmd);
		else
		{
			pid[data.pid_index] = fork();
			if (pid[data.pid_index] == 0)
			{
				connect_pipe(data.pid_index, process, pipe_fd);
				find_redirect(lst, data.tmp_arr, data.tmp_arr_index);
				execute_command(vars, data.cmd, data.envp);
			}
		}
		use_free(data.cmd);
		move_next_syntax(&lst, pipe_fd, &(data.tmp_arr_index), &data.pid_index);
	}
	clear_resources(data.envp, process, pipe_fd, data.tmp_arr);
}

void	move_next_syntax(t_list **lst, int (*pipe_fd)[2], int *tmp_arr_index,
		int *pid_index)
{
	if (*pid_index != 0)
		close_last_pipe(pipe_fd, *pid_index);
	while (*lst != NULL && ft_strncmp((*lst)->token, "|", 2) != 0)
	{
		if ((*lst)->state == HEREDOC)
			(*tmp_arr_index)++;
		*lst = (*lst)->next;
	}
	if (*lst != NULL)
		*lst = (*lst)->next;
	(*pid_index)++;
}

void	execute_command(t_vars *vars, char **cmd, char **envp)
{
	char	**path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	path = parse_path(vars->env);
	if (is_builtin(cmd))
		exit(builtin_func(vars, cmd));
	else
	{
		cmd[0] = path_join(path, cmd[0]);
		use_execve(cmd[0], cmd, envp);
	}
}

void	wait_child(pid_t *pid, int process)
{
	int	i;
	int	j;

	i = 0;
	while (i < process - 1)
	{
		j = 0;
		while (j < process - 1)
		{
			if (waitpid(pid[j], &g_status, WNOHANG) > 0)
			{
				if (WIFEXITED(g_status))
					g_status = WEXITSTATUS(g_status);
				++i;
			}
			++j;
		}
	}
	waitpid(pid[process - 1], &g_status, 0);
	if (g_status == 2 || g_status == 3)
		g_status += 128;
	else if (WIFEXITED(g_status))
		g_status = WEXITSTATUS(g_status);
}
