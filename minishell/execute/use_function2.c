#include "../minishell.h"

pid_t	use_waitpid(pid_t pid, int *stat_loc, int options)
{
	pid_t	result;

	result = waitpid(pid, stat_loc, options);
	if (result == -1)
	{
		perror("waitpid error");
		exit(1);
	}
	return (result);
}

void	use_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		perror("dup2 error");
		exit(1);
	}
}

void	use_close(int fd)
{
	if (close(fd) == -1)
	{
		perror("close error");
		exit(1);
	}
}

int	infile_open(const char *path, int oflag)
{
	int	fd;

	fd = open(path, oflag);
	if(fd == -1)
	{
		perror("open error");
		exit(1);
	}
	return (fd);
}

// int	outfile_open(const char *path, int status)
// {
// 	int	fd;

// 	if(status == REDIRECTION)
// 		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	else
// 		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
// 	if (fd == -1)
// 	{
// 		perror("open error");
// 		exit(1);
// 	}
// 	return (fd);
// }
