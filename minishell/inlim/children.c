#include "../minishell.h"

void	just_one_cmd(t_execve data)
{
	use_use_execve(data.cmd[0], data.cmd, data.envp);
}

void	first_cmd(int **pipe_fd, t_execve data)
{
	char	**cmd;
	
	use_close(pipe_fd[0][0]);
	// stdout을 pipe_fd[process_index][1]로 변경.
	change_stdout_to_pipe(pipe_fd[0]);
	use_execve(data.cmd[0], data.cmd, data.envp);
}

void	middle_cmd(int pid_index, int **pipe_fd, t_execve data)
{
	char	**cmd;

	use_close(pipe_fd[pid_index - 1][1]);
	use_close(pipe_fd[pid_index][0]);
	//stdin을 pipe_fd[process_index - 1][0].
	change_stdin_to_pipe(pipe_fd[pid_index -1]);
	//stdout을 pipe_fd[process_index][1]로 변경.
	change_stdout_to_pipe(pipe_fd[pid_index]);
	use_execve(cmd[0], cmd, data.envp);
}

void	last_cmd(int pid_index, int **pipe_fd, t_execve data)
{
	char	**cmd;

	use_close(pipe_fd[pid_index -1][1]);
	// stdin을 pipe_fd[pid_index - 1][0]으로 변경.
	change_stdin_to_pipe(pipe_fd[pid_index -1]);
	use_execve(cmd[0], cmd, data.envp);
}


void	child(int pid_index, int last_pid_index, int **pipe_fd, t_execve data)
{
	if(pid_index == 0 && pid_index == last_pid_index)
		just_one_cmd(data);
	else if(pid_index == 0)
		first_cmd(pipe_fd, data);
	else if(pid_index != last_pid_index)
		middle_cmd(pid_index, pipe_fd, data);
	else
		last_cmd(pid_index, pipe_fd, data);
}
