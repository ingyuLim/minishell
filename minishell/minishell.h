#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <term.h>
# include <termios.h>
# include <readline/history.h>
# include <readline/readline.h>

int	g_status;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_vars
{
	t_list	*lst;
	t_env	*env;
}				t_vars;

// error.c
void	error(char *err);
void	exit_with_msg(char *msg);
void	exit_with_err(char *err);

// utils.c
void	leak(void);
void	print_tokens(t_list *lst);
void	free_strtok(char *str, t_list **lst);

// parse.c
char	*meet_quote(char *str, int *i, char quote);
char	*meet_sep(char *str, int *i);
char	*make_word(char *str, int *i);
char	*make_symbol(char *str, char c, int *i);
t_list	*tokenize(char *str);

// syntax.c
void	print_green(char *str);
void	print_red(char *str);
int		syntax_check(t_list *head);

// builtin/builtin_utils.c
int		ft_isvalidkey(char *key);
int		ft_isspecialtok(t_state state);
t_env	*ft_envlast(t_env *env);
void	ft_envadd_back(t_env **head, t_env *new);
t_env	*make_env(char *content);
t_env	*dup_env(char *envp[]);

// builtin/*.c
int		b_cd(char **cmd);
int		b_pwd(void);
int		b_echo(char **cmd);
int		b_export(char **cmd, t_env *env);
int		b_env(char **cmd, t_env *env);
int		b_exit(char **cmd);
int		b_unset(char **cmd, t_env **env);

// execve/change_in_and_out.c
void	change_stdin_to_pipe(int *pipe_fd);
void	change_stdout_to_pipe(int *pipe_fd);

// inlim/children.c
void	first_cmd(int (*pipe_fd)[2]);
void	middle_cmd(int pid_index, int (*pipe_fd)[2]);
void	last_cmd(int pid_index, int (*pipe_fd)[2]);

// execute/execute.c
int		process_count(t_list *lst);
int		cmd_size_count(t_list *lst);
char	**make_cmd(t_list *lst);
char	**make_envp(t_env *env);
char	*path_join(char **path, char *cmd);
void	free_envp(char **envp);
void	move_next_syntax(t_list **lst, int *tmp_arr_index);
void	find_redirect(t_list *lst, char **tmp_arr, int tmp_arr_index);
void	connect_pipe(t_vars *vars, pid_t *pid, int process, char **path);
int		builtin_func(t_vars *vars, char **cmd);
int		is_builtin(char **cmd);
char	**parse_path(t_env *env);
void	free_path(char **path);
void	execute(t_vars *vars);

// inlim/use_function1.c
void	use_execve(char *path, char *argv[], char *envp[]);
void	use_pipe(int *fd);
pid_t	use_fork(void);

// inlim/use_function2.c
pid_t	use_waitpid(pid_t pid, int *stat_loc, int options);
void	use_dup2(int fd1, int fd2);
void	use_close(int fd);
int		infile_open(const char *path, int oflag);
int		outfile_open(const char *path, int status);

// env_vars
int		is_include_dollar(char *str);
char	*replace_tokens(char *content, t_env *env);
void	replace_envvar(t_vars *vars);
void	execute(t_vars *vars);

#endif
