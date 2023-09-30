#include "../minishell.h"

void	first_cmd(int (*pipe_fd)[2])
{
	use_close(pipe_fd[0][0]);
	// stdout을 pipe_fd[process_index][1]로 변경.
	change_stdout_to_pipe(pipe_fd[0]);
}

void	middle_cmd(int pid_index, int (*pipe_fd)[2])
{
	use_close(pipe_fd[pid_index - 1][1]);
	use_close(pipe_fd[pid_index][0]);
	//stdin을 pipe_fd[process_index - 1][0].
	change_stdin_to_pipe(pipe_fd[pid_index -1]);
	//stdout을 pipe_fd[process_index][1]로 변경.
	change_stdout_to_pipe(pipe_fd[pid_index]);
}

void	last_cmd(int pid_index, int (*pipe_fd)[2])
{
	use_close(pipe_fd[pid_index -1][1]);
	// stdin을 pipe_fd[pid_index - 1][0]으로 변경.
	change_stdin_to_pipe(pipe_fd[pid_index -1]);
}

void	connect_pipe(int pid_index, int process, int (*pipe_fd)[2])
{
	if(pid_index == 0 && pid_index == process - 1)
		;
	else if(pid_index == 0)
		first_cmd(pipe_fd);//cmd 라고 하지 말고 syntax라고 하기.
	else if(pid_index != process - 1)
		middle_cmd(pid_index, pipe_fd);
	else
		last_cmd(pid_index, pipe_fd);
}
