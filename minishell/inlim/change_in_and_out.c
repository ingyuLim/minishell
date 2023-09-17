#include "../minishell.h"

// void	change_stdin_to_infile(t_execve data)
// {
// 	int	infile_fd;

// 	infile_fd = infile_open(data.infile, O_RDONLY);
// 	use_dup2(infile_fd, STDIN_FILENO);
// 	use_close(infile_fd);
// }

void	change_stdin_to_pipe(int *pipe_fd)
{
	use_dup2(pipe_fd[0], STDIN_FILENO);
	use_close(pipe_fd[0]);
}

// void	change_stdout_to_outfile(t_execve data)
// {
// 	int	outfile_fd;

// 	outfile_fd = outfile_open(data.outfile, data.status);
// 	use_dup2(outfile_fd, STDOUT_FILENO);
// 	use_close(outfile_fd);
// }

void	change_stdout_to_pipe(int *pipe_fd)
{
	use_dup2(pipe_fd[1], STDOUT_FILENO);
	use_close(pipe_fd[1]);
}
