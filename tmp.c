void	execute(t_vars *vars, pid_t *pid, int (*pipe_fd)[2], int process)
{
	t_list		*lst;
	t_execute	data;

	init_variable(vars, &lst, &data);
	while (process > data.pid_index) //cmd가 있는 경우.
	{
		data.cmd = make_cmd(lst);
		if (data.pid_index != process - 1)
			pipe(pipe_fd[data.pid_index]);
		if(is_builtin(data.cmd) && data.pid_index == process - 1 && !ft_is_redirection(lst))
			last_builtin(vars, data.cmd, data.pid_index, pipe_fd);
		else
		{
			pid[data.pid_index] = fork();
			if (pid[data.pid_index] == 0)
			{
				connect_pipe(data.pid_index, process, pipe_fd);
				find_redirect(lst, data.tmp_arr,data.tmp_arr_index);
				execute_command(vars, data.cmd, data.envp);
			}
		}
		use_free(data.cmd);
		move_next_syntax(&lst, pipe_fd, &(data.tmp_arr_index),&data.pid_index);
	}
	clear_resources(data.envp, process, pipe_fd, data.tmp_arr);
}
