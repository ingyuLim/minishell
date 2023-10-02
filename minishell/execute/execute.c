#include "../minishell.h"

int	process_count(t_list *lst)
{
	int	process;

	process = 1;
	while(lst != NULL)
	{
		if(ft_strncmp(lst->token, "|", 2) == 0)
			process++;
		lst = lst->next;
	}
	return (process);
}

int	cmd_size_count(t_list *lst)
{
	int	size;

	size = 1;
	while(lst != NULL && ft_strncmp(lst->token, "|", 2) != 0 )
	{
		size++;
		lst = lst->next;
	}
	 return (size);
}

int	count_cmd_count(t_list *lst)
{
	int	len;

	len = 1;
	while(lst != NULL && ft_strncmp((lst)->token, "|", 2) != 0)
	{
		if(lst->state == CMD)
			len++;
		lst = (lst)->next;
	}
	return len;
}

char	**make_cmd(t_list *lst)
{
	int		i;
	int		cmd_len;
	char	**cmd;

	i = 0;
	cmd_len = count_cmd_count(lst);
	cmd = ft_calloc(cmd_len + 1, sizeof(char *));
	while(lst != NULL && lst->state != PIPE)
	{
		if(lst->state == CMD)
		{
			cmd[i] = (lst)->token;
			i++;
		}
		lst = (lst)->next;
	}
	return (cmd);
}

char	**make_envp(t_env *env)
{
	char	**envp;
	t_env	*tmp;
	char	*mem;
	int		i;

	tmp = env;
	i = 0;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	envp = (char **)ft_calloc((i + 1), sizeof(char *));
	i = 0;
	while (env != NULL)
	{
		mem = ft_strjoin(env->key, "=");
		envp[i] = ft_strjoin(mem, env->value);
		use_free(mem);
		env = env->next;
		++i;
	}
	return (envp);
}

char	*path_join(char **path, char *cmd)
{
	char	*tmp;
	int		i;

	if (path == NULL)
		return (cmd);
	i = 0;
	while (path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], cmd);
		if (access(tmp, X_OK) == 0)
			break ;
		use_free(tmp);
		++i;
	}
	if (path[i] == NULL)
		return (cmd);
	return (tmp);
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		use_free(envp[i]);
		++i;
	}
	use_free(envp);
}

void	move_next_syntax(t_list **lst, char **cmd, int *tmp_arr_index, int *pid_index)
{
	while(*lst != NULL && ft_strncmp((*lst)->token, "|", 2) != 0)
	{
		if((*lst)->state == HEREDOC)
			(*tmp_arr_index)++;
		*lst = (*lst)->next;
	}
	if (*lst != NULL)
		*lst = (*lst)->next;
	(*pid_index)++;
	use_free(cmd);
}

void	find_in_redir(t_list **lst)
{
	int	infile_fd;

	*lst = (*lst)->next;
	infile_fd = open((*lst)->token, O_RDONLY);
	use_dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
}

void	find_out_redir(t_list **lst)
{
	int	outfile_fd;

	*lst = (*lst)->next;
	outfile_fd = open((*lst)->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	use_dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
}

void	find_heredoc(char **tmp_arr, int tmp_arr_index)
{
	int	infile_fd;

	infile_fd = open(tmp_arr[tmp_arr_index], O_RDONLY);
	use_dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	unlink(tmp_arr[tmp_arr_index]);
	tmp_arr_index++;
}

void	find_pair_out_redir(t_list **lst)
{
	int	outfile_fd;

	*lst = (*lst)->next;
	outfile_fd = open((*lst)->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
	use_dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
}

void	find_redirect(t_list *lst, char **tmp_arr, int tmp_arr_index)// + int	tmp_arr_index 추가하기. 일단은 i로 선언해서 쓰자.
{
	while(lst != NULL && lst->state != PIPE)
	{
		if(lst->state == IN_REDIR) // <
			find_in_redir(&lst);
		else if(lst->state == OUT_REDIR) // >
			find_out_redir(&lst);
		else if(lst->state == HEREDOC)
			find_heredoc(tmp_arr, tmp_arr_index);
		else if(lst->state == PAIR_OUT_REDIR)
			find_pair_out_redir(&lst);
		lst = lst->next;
	}
}

char	**malloc_tmp_arr(t_list *lst)
{
	char	**tmp_arr;
	int		i;

	tmp_arr = NULL;
	i = 0;
	while(lst != NULL)
	{
		if(lst->state == HEREDOC)
			i++;
		lst = (lst)->next;
	}
	if(i != 0)
		tmp_arr = ft_calloc(i + 1, sizeof(char *));
	return (tmp_arr);
}

int	exist_nl(char *buf)
{
	while(*buf)
	{
		if(*buf == '\n')
			return 1;
		buf++;
	}
	return 0;
}

size_t	gnl_strlen(char *str)
{
	int	result_len;

	result_len = 0;
	while (*str)
	{
		result_len++;
		if (*str == '\n')
			break ;
		str++;
	}
	return (result_len);
}

char *naming_tmp_file(char *tmp_file)
{
	int		num;
	char	*letter_num;
	char	*tmp_filename;

	num = 0;
	letter_num = ft_itoa(num++);
	tmp_filename = ft_strjoin(tmp_file,letter_num);
	use_free(letter_num);
	while(access(tmp_filename,F_OK) != -1)
	{
		if(tmp_filename != NULL)
			use_free(tmp_filename);
		letter_num = ft_itoa(num++);
		tmp_filename = ft_strjoin(tmp_file,letter_num);
		use_free(letter_num);
	}
	return (tmp_filename);
}

void	write_in_tmpfile(t_list *lst, int tmp_fd)
{
	char	*limiter;
	size_t	buffer_size;
	char	*buf;
	int		nl_flag;

	limiter = lst->next->token;
	buffer_size = ft_strlen(limiter) + 1;
	buf = ft_calloc(buffer_size, sizeof(char));
	nl_flag = 1;
	ft_putstr_fd("\033[0;30m", 1);
	ft_putstr_fd("> ", 1);
	while (read(0, buf, buffer_size))
	{
		if (!ft_strncmp(limiter, buf, buffer_size - 1) && buf[buffer_size - 1] == '\n' && nl_flag)
			break;
		else if (exist_nl(buf))
		{
			nl_flag = 1;
			ft_putstr_fd("> ", 1);
		}
		else
			nl_flag = 0;
		write(tmp_fd, buf, gnl_strlen(buf));
	}
	use_free(buf);
}


void	fill_tmp_arr(char **tmp_arr, t_list *lst)
{
	int		i = 0;
	char	*tmp_filename = NULL;
	int		tmp_fd;

	while(lst != NULL)
	{
		if(lst->state == HEREDOC)
		{
			tmp_filename = naming_tmp_file(".tmp");
			// if (access(tmp_filename, F_OK) == -1)
				// error
			tmp_fd = open(tmp_filename, O_RDWR | O_CREAT, 0644);
			tmp_arr[i] = tmp_filename;
			write_in_tmpfile(lst, tmp_fd);
			use_close(tmp_fd);
			i++;
		}
		lst = lst->next;
	}
	ft_putstr_fd("\033[0m", 1);
}

 int	ft_is_redirection(t_list *lst)
 {
	while(lst != NULL && lst->state != PIPE)
	{
		if(lst->state ==IN_REDIR || lst->state== OUT_REDIR|| lst->state==HEREDOC||lst->state==PAIR_OUT_REDIR)
			return (1);
		lst=lst->next;
	}
	return 0;
 }

void	free_tmp_arr(char **tmp_arr)
{
	int	i;

	i = 0;
	while(tmp_arr[i] != NULL)
	{
		use_free(tmp_arr[i]);
		i++;
	}
	use_free(tmp_arr);
}

void	last_builtin(t_vars *vars, char	**cmd, int pid_index, int (*pipe_fd)[2])
{
	if(pid_index != 0)
		last_cmd(pid_index, pipe_fd);
	builtin_func(vars, cmd);
}



void	execute_command(t_vars *vars, char **cmd, char	**envp)
{
	char **path;

	path = parse_path(vars->env);
	if(is_builtin(cmd))
		exit(builtin_func(vars, cmd));
	else
	{
		cmd[0] = path_join(path, cmd[0]);
		use_execve(cmd[0], cmd, envp);
	}
}

void	clear_resources(char **envp, int process,int (*pipe_fd)[2],char **tmp_arr)
{
	free_envp(envp);
	if (process > 1)
		use_free(pipe_fd);
	if(tmp_arr != NULL)
		free_tmp_arr(tmp_arr);
}

void	close_last_pipe(int (*pipe_fd)[2], int pid_index)
{
	close(pipe_fd[pid_index - 1][0]);
	close(pipe_fd[pid_index - 1][1]);
}

void	init_variable(t_vars *vars, t_list **lst, t_execute *data)
{
	*lst = vars->lst;
	data->pid_index = 0;
	data->tmp_arr = malloc_tmp_arr(*lst);
	fill_tmp_arr(data->tmp_arr, *lst);//fill_tmp_arr
	data->tmp_arr_index = 0;
	data->envp = make_envp(vars->env);
}

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

void	close_last_pipe(int (*pipe_fd)[2], int pid_index)
{
	close(pipe_fd[pid_index - 1][0]);
	close(pipe_fd[pid_index - 1][1]);
}

void	init_variable(t_vars *vars, t_list **lst, t_execute *data)
{
	*lst = vars->lst;
	data->pid_index = 0;
	data->tmp_arr = malloc_tmp_arr(*lst);
	fill_tmp_arr(data->tmp_arr, *lst);//fill_tmp_arr
	data->tmp_arr_index = 0;
	data->envp = make_envp(vars->env);
}
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
		if(data.pid_index != 0)
			close_last_pipe(pipe_fd, data.pid_index);
		move_next_syntax(&lst, data.cmd, &(data.tmp_arr_index),&data.pid_index);
	}
	clear_resources(data.envp, process, pipe_fd, data.tmp_arr);
}

int	is_builtin(char **cmd)
{
	if (cmd[0] == NULL)
		return (0);
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		return (1);
	return (0);
}

int	builtin_func(t_vars *vars, char **cmd)
{
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		g_status = b_cd(cmd);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		g_status = b_pwd();
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		g_status = b_echo(cmd);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		g_status = b_export(cmd, vars->env);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		g_status = b_env(vars->env);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		g_status = b_unset(cmd, &(vars->env));
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		g_status = b_exit(cmd);
	return (g_status);
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

void	execute_frame(t_vars *vars)
{
	int		process;
	int		(*pipe_fd)[2];
	pid_t	*pid;

	signal(SIGINT, sigint_handler_exec);
	replace_env_and_trim_quote(vars);
	// print_tokens(vars->lst);
	process = process_count(vars->lst);
	pipe_fd = NULL;
	pid = ft_calloc(process, sizeof(pid_t));
	if(process > 1)
		pipe_fd = ft_calloc(process - 1, sizeof(int [2]));
	execute(vars, pid, pipe_fd, process);
	wait_child(pid, process);
	use_free(pid);
}

void	wait_child(pid_t *pid, int process)
{
	int	i;
	int	j;

	j = 0;
	while (j < process - 1)
	{
		i = 0;
		while (i < process - 1)
		{
			if (waitpid(pid[i], &g_status, WNOHANG) == pid[i])
			{
				if (WIFEXITED(g_status))
					g_status = WEXITSTATUS(g_status);
				++j;
			}
			++i;
		}

	}
	waitpid(pid[process - 1], &g_status, 0);
	if (g_status == 2)
		g_status = 130;
	else if (WIFEXITED(g_status))
		g_status = WEXITSTATUS(g_status);
}
