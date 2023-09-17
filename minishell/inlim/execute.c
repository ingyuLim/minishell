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
	return process;
}

int	size_count(t_list *lst)
{
	int	size;

	size = 1;
	while(lst != NULL && ft_strncmp(lst->token, "|", 2) != 0 )
	{
		size++;
		lst = lst->next;
	}
	 return size;
}

char	**make_cmd(t_list **lst, int size)
{
	int		i;
	char	**cmd;

	i = 0;
	cmd = ft_calloc(size, sizeof(char *));
	while(*lst != NULL && ft_strncmp((*lst)->token, "|", 2) != 0)
	{
		cmd[i] = (*lst)->token;
		*lst = (*lst)->next;
	}
	return cmd;
}

int	**pipe_malloc(int pipe_count)
{
	int	**pipe_fd;
	int	i;

	pipe_fd = malloc(sizeof(int *) * pipe_count);
	if(pipe_fd == NULL)
	{
		perror("malloc");
		exit(1);
	}
	i = 0;
	while(i < pipe_count)
	{
		pipe_fd[i] = malloc(sizeof(int) * 2);
		if(pipe_fd[i] == NULL)
		{
			perror("malloc");
			exit(1);
		}
		i++;
	}
	return (pipe_fd);
}

void	check_xfile(char **cmd, char **path)
{
	if (check_slash(cmd[0]) != 0)
	{
		if (relative_path(cmd, path))
			return ;
	}
	else
	{
		if (absolute_path(cmd))
			return ;
	}
	perror("Command not found");
	exit(1);
}


void	connect_pipe(t_list *lst, pid_t *pid, int process, t_execve data)
{
	int		**pipe_fd;
	int		i;
	int		size;
	char	**cmd;

	if(process > 1)
		pipe_fd = pipe_malloc(process - 1);
	i = 0;
	while (process > i) //cmd가 있는 경우.
	{
		size = size_count(lst);
		cmd = make_cmd(&lst, size);
		if(i != process - 1)
			pipe(pipe_fd[i]);
		pid[i] = fork();
		if (pid[i] == 0)
		{
			check_xfile(cmd, data.path);
			data.cmd = cmd;
			child(i, process - 1, pipe_fd, data);//status추가.
		}
		free(cmd);
		if(i != 0)
		{
			close(pipe_fd[i - 1][0]);     //근데 close 실패하면 원래 exit이 맞나? 글고 애초에 실패할 일이 있으려나 일케 하면...?
			close(pipe_fd[i - 1][1]);
		}
		i++;
	}
}

void	execute(t_list *lst, char *envp[])
{
	t_execve data;
	int		process;
	pid_t	*pid;
	int		stat;

	if (ft_strncmp(lst->token, "cd", 3) == 0)
		cd(lst);
	else if (ft_strncmp(lst->token, "pwd", 4) == 0)
		pwd();
	else if (ft_strncmp(lst->token, "echo", 5) == 0)
		echo(lst);
	else
	{
		data.path = parsing_path(envp);
		data.envp = envp;
		process = process_count(lst);
		pid = ft_calloc(process, sizeof(pid_t));
		connect_pipe(lst, pid, process, data);
		use_waitpid(pid[process - 1], &stat, 0);
		while(wait(NULL) != -1);
	}
}

// 리다이렉션 여러개일 때 어떻게 할건지 토의 필요.
// cat < outfile < infile > infile 하면 infile이 빈 파일이 되는데
// cat < outfile < infile > infile2 하면 infile2 제대로 입력됨.