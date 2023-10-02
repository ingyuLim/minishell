#include "../minishell.h"

void	change_stdin_to_pipe(int *pipe_fd)
{
	use_dup2(pipe_fd[0], STDIN_FILENO);
	use_close(pipe_fd[0]);
}

void	change_stdout_to_pipe(int *pipe_fd)
{
	use_dup2(pipe_fd[1], STDOUT_FILENO);
	use_close(pipe_fd[1]);
}
