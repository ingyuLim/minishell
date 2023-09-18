#include "../minishell.h"

void	use_execve(char *path, char *argv[], char *envp[])
{
	if (execve(path, argv, envp) == -1)
		exit_with_err((char *)path);
}

void	use_pipe(int *fd)
{
	if (pipe(fd) == -1)
		exit_with_err("pipe");
}

pid_t	use_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_with_err("fork");
	return (pid);
}
