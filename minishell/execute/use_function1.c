#include "../minishell.h"

void	use_execve(const char *path, char *const argv[], char *const envp[])
{
	if (execve(path, argv, envp) == -1)
	{
		while(*path)
		{
			write(2,path,1);
			path++;
		}
		write(2," <- ",4);
		perror("execve error");
		exit(1);
	}
}

void	use_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe error");
		exit(1);
	}
	else
		return ;
}

pid_t	use_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		exit(1);
	}
	else
		return (pid);
}
