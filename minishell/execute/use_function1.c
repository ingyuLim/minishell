#include "../minishell.h"

void	use_execve(char *path, char *argv[], char *envp[])
{
	g_status = 0;
	if (execve(path, argv, envp) == -1)
	{
		g_status = 1;
		exit_with_err(path, 0);
	}
}

void	use_pipe(int *fd)
{
	if (pipe(fd) == -1)
		exit_with_err("pipe", 0);
}

pid_t	use_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_with_err("fork", 0);
	return (pid);
}

void	use_free(void *mem)
{
	ft_bzero((char *)mem, ft_strlen(mem));
	free(mem);
}
