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

void	move_next_syntax(t_list **lst)
{
	while(*lst != NULL && ft_strncmp((*lst)->token, "|", 2) != 0)
		*lst = (*lst)->next;
	if (*lst != NULL)
		*lst = (*lst)->next;
}

char *	make_tmp_file(char *tmp_file)
{
	char *result;
	int	num = 0;
	char	*letter_num;

	letter_num = ft_itoa(num);
	result = ft_strjoin(tmp_file,letter_num);

	while(access(result,F_OK) != -1)
	{
		free(letter_num);
		free(result);
		letter_num = ft_itoa(++num);
		result = ft_strjoin(tmp_file,letter_num);
	}
	// if(access(result,F_OK) != -1)
		//error
	free(letter_num);
	open(result, O_WRONLY | O_CREAT, 0644);
	return result;
}

void	here_doc(char *limiter)
{
	// size_t	buffer_size = ft_strlen(limiter) + 1;
	// char	*buf = malloc(sizeof(char) * buffer_size);
	// int	nl_flag = 1;
	char *tmp_file;
	tmp_file = make_tmp_file("tmp");
	limiter = NULL;
	// tmp 안에 써야한다.
	// while(read(0, buf, buffer_size)) fd를 2(STDERR)로 해야하나...
	// {
	// 	if(!ft_strncmp(limiter, buf, buffer_size - 1) && buf[buffer_size - 1] == '\n' && nl_flag)
	// 		break;
	// 	else if(exist_nl(buf))
	// 		nl_flag = 1;
	// 	else
	// 		nl_flag = 0;
	// }

	//나중에
	// unlink(tmp_file);
	// free(tmp_file);
}

void	find_redirect(t_list *lst)
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
			use_dup2(STDOUT_FILENO, outfile_fd);
			close(outfile_fd);
		}
		else if(lst->state == PAIR_IN_REDIR)
		{
			// here_doc(lst->next->token);
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


void	connect_pipe(t_vars *vars, pid_t *pid, int process, char **path)
{
	int		(*pipe_fd)[2];
	int		pid_index;
	char	**cmd;
	char	**envp;
	t_list	*lst;

	lst = vars->lst;
	envp = make_envp(vars->env);
	if(process > 1)
		pipe_fd = ft_calloc(process - 1, sizeof(int [2]));
	pid_index = 0;
	while (process > pid_index) //cmd가 있는 경우.
	{
		if(pid_index != process - 1)
			pipe(pipe_fd[pid_index]);
		pid[pid_index] = fork();
		if (pid[pid_index] == 0)
		{
			// find_redirect(lst); 삭제하고 ~cmd 함수로 옮김.
			// builtin_fuc(vars);
			cmd = make_cmd(lst);
			cmd[0] = path_join(path, cmd[0]);
			// child(i, process - 1, pipe_fd, cmd, envp);//status추가.
			if(pid_index == 0 && pid_index == process - 1)
				;
			else if(pid_index == 0)
				first_cmd(pipe_fd);
			else if(pid_index != process - 1)
				middle_cmd(pid_index, pipe_fd);
			else
				last_cmd(pid_index, pipe_fd);
			find_redirect(lst);
			use_execve(cmd[0], cmd, envp);
		}
		// free(cmd);
		if(pid_index != 0)
		{
			close(pipe_fd[pid_index - 1][0]);     //근데 close 실패하면 원래 exit이 맞나? 글고 애초에 실패할 일이 있으려나 일케 하면...?
			close(pipe_fd[pid_index - 1][1]);
		}
		move_next_syntax(&lst);
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

// 리다이렉션 여러개일 때 어떻게 할건지 토의 필요.
// cat < outfile < infile > infile 하면 infile이 빈 파일이 되는데
// cat < outfile < infile > infile2 하면 infile2 제대로 입력됨.
