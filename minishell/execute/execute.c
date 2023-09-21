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
		// printf("token : %s, state : %d\n",lst->token, lst->state);
		if(lst->state == CMD)
		{
			cmd[i] = (lst)->token;
			// printf("cmd[%d] : %s\n",i,lst->token);
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
		free(mem);
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
		free(tmp);
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
		free(envp[i]);
		++i;
	}
	free(envp);
}

void	move_next_syntax(t_list **lst, int *tmp_arr_index)
{
	while(*lst != NULL && ft_strncmp((*lst)->token, "|", 2) != 0)
	{
		if((*lst)->state == HEREDOC)
			(*tmp_arr_index)++;
		*lst = (*lst)->next;
	}
	if (*lst != NULL)
		*lst = (*lst)->next;
}


void	find_redirect(t_list *lst, char **tmp_arr, int tmp_arr_index)// + int	tmp_arr_index 추가하기. 일단은 i로 선언해서 쓰자.
{
	int	infile_fd;
	int	outfile_fd;

	while(lst != NULL && lst->state != PIPE)
	{
		if(lst->state == IN_REDIR) // <
		{
			lst = lst->next;
			infile_fd = open(lst->token, O_RDONLY);
			use_dup2(infile_fd, STDIN_FILENO);
			close(infile_fd);
		}
		else if(lst->state == OUT_REDIR) // >
		{
			lst = lst->next;
			outfile_fd = open(lst->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			use_dup2(outfile_fd, STDOUT_FILENO);
			close(outfile_fd);
		}
		else if(lst->state == HEREDOC)
		{
			infile_fd = open(tmp_arr[tmp_arr_index], O_RDONLY);
			use_dup2(infile_fd, STDIN_FILENO);
			close(infile_fd);
			unlink(tmp_arr[tmp_arr_index]);
			tmp_arr_index++;
		}
		else if(lst->state == PAIR_OUT_REDIR)
		{
			lst = lst->next;
			outfile_fd = open(lst->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
			use_dup2(outfile_fd, STDOUT_FILENO);
			close(outfile_fd);
		}
		lst = (lst)->next;
	}
}

char	**malloc_tmp_arr(t_list *lst)
{
	char	**tmp_arr;
	int		i;

	i = 0;
	while(lst != NULL)
	{
		if(lst->state == HEREDOC)
			i++;
		lst = (lst)->next;
	}
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

void	fill_tmp_arr(char *tmp_file, char **tmp_arr, t_list *lst)
{
	int		num = 0;
	int		i = 0;
	char	*tmp_filename = NULL;
	char	*letter_num;
	char	*limiter;
	char	*buf;
	int		tmp_fd;
	size_t	buffer_size;
	int	nl_flag = 1;

	while(lst != NULL)
	{
		if(lst->state == HEREDOC)
		{
			letter_num = ft_itoa(num++);
			tmp_filename = ft_strjoin(tmp_file,letter_num);
			free(letter_num);
			while(access(tmp_filename,F_OK) != -1)
			{
				if(tmp_filename != NULL)
					free(tmp_filename);
				letter_num = ft_itoa(num++);
				tmp_filename = ft_strjoin(tmp_file,letter_num);
				free(letter_num);
			}
			// if (access(tmp_filename, F_OK) == -1)
				// error
			tmp_fd = open(tmp_filename, O_RDWR | O_CREAT, 0644);
			tmp_arr[i] = tmp_filename;
			limiter = lst->next->token;
			buffer_size = ft_strlen(limiter) + 1;
			buf = ft_calloc(buffer_size, sizeof(char));
			while(read(0, buf, buffer_size))
			{
				if(!ft_strncmp(limiter, buf, buffer_size - 1) && buf[buffer_size - 1] == '\n' && nl_flag)
					break;
				else if(exist_nl(buf))
					nl_flag = 1;
				else
					nl_flag = 0;
				write(tmp_fd, buf, gnl_strlen(buf));
			}
			use_close(tmp_fd);
			i++;
			free(buf);
		}
		lst = lst->next;
	}
}

void	connect_pipe(t_vars *vars, pid_t *pid, int process, char **path)
{
	int		(*pipe_fd)[2];
	int		pid_index;
	char	**tmp_arr;
	int		tmp_arr_index = 0;
	char	**cmd;
	char	**envp;
	t_list	*lst;

	lst = vars->lst;
	envp = make_envp(vars->env);
	if(process > 1)
		pipe_fd = ft_calloc(process - 1, sizeof(int [2]));
	pid_index = 0;
	tmp_arr = malloc_tmp_arr(lst);
	fill_tmp_arr(".tmp", tmp_arr, lst);//fill_tmp_arr
	while (process > pid_index) //cmd가 있는 경우.
	{
		if (pid_index != process - 1)
			pipe(pipe_fd[pid_index]);
		pid[pid_index] = fork();
		if (pid[pid_index] == 0)
		{
			// builtin_fuc(vars);
			cmd = make_cmd(lst);
			cmd[0] = path_join(path, cmd[0]);
			if(pid_index == 0 && pid_index == process - 1)
				;
			else if(pid_index == 0)
				first_cmd(pipe_fd);
			else if(pid_index != process - 1)
				middle_cmd(pid_index, pipe_fd);
			else
				last_cmd(pid_index, pipe_fd);
			find_redirect(lst, tmp_arr,tmp_arr_index);
			use_execve(cmd[0], cmd, envp);
		}
		// free(cmd);
		if(pid_index != 0)
		{
			close(pipe_fd[pid_index - 1][0]);     //근데 close 실패하면 원래 exit이 맞나? 글고 애초에 실패할 일이 있으려나 일케 하면...?
			close(pipe_fd[pid_index - 1][1]);
		}
		move_next_syntax(&lst, &tmp_arr_index);
		pid_index++;
	}
	free_envp(envp);
	if (process > 1)
		free(pipe_fd);
}

int	builtin_fuc(t_vars *vars)
{
	t_list	*lst;

	lst = vars->lst;
	if (ft_strncmp(lst->token, "cd", 3) == 0)
		b_cd(&lst);
	else if (ft_strncmp(lst->token, "pwd", 4) == 0)
		b_pwd();
	else if (ft_strncmp(lst->token, "echo", 5) == 0)
		b_echo(&lst);
	else if (ft_strncmp(lst->token, "export", 7) == 0)
		b_export(&lst, vars->env);
	else if (ft_strncmp(lst->token, "env", 4) == 0)
		b_env(&lst, vars->env);
	else if (ft_strncmp(lst->token, "unset", 6) == 0)
		b_unset(&lst, &(vars->env));
	else if (ft_strncmp(lst->token, "exit", 5) == 0)
		b_exit(&lst);
	return (1);
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
		free(path[i]);
		i++;
	}
	free(path);
}

void	execute(t_vars *vars)
{
	char		**path;
	int			process;
	pid_t		*pid;
	int			stat;

	path = parse_path(vars->env);
	process = process_count(vars->lst);
	pid = ft_calloc(process, sizeof(pid_t));
	connect_pipe(vars, pid, process, path);
	use_waitpid(pid[process - 1], &stat, 0);
	while(wait(NULL) != -1);
	free_path(path);
	free(pid);
}


// sleep 1 << limiter1 < infile > outfile | ls << limiter2 < infile2 <infile3
// 히어독 먼저 세고 그만큼 tmp파일의 fd를 담을 배열 malloc한 후 순서대로 입력을 담아주고 그 후 find rediection을 통해 입출력 방향 바꾸기. 그 후 tmp 파일 삭제.