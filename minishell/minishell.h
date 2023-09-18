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

typedef enum	e_state{
	START,					// 명령어의 시작
	PIPE,					// |
	IN_REDIRECT,			// <
	OUT_REDIRECT,			// >
	WORD,					// command or argument or file name
	DOUBLE_IN_REDIRECT,		// <<
	DOUBLE_OUT_REDIRECT,	// >>
} t_state;

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

typedef struct s_execve
{
    char    **envp;
    char    **path;
    char    **cmd;
}t_execve;

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

// builtin.c
t_env	*ft_envlast(t_env *env);
void	ft_envadd_back(t_env **head, t_env *new);
t_env	*make_env(char *contents);
t_env	*dup_env(char *envp[]);
int		b_cd(t_list *lst);
int		b_pwd(void);
int		b_echo(t_list *lst);
int		b_export(t_list *lst, t_env *env);
int		b_env(t_list *lst, t_env *env);
int		b_exit(t_list *lst);

// inlim/change_in_and_out.c
void	change_stdin_to_pipe(int *pipe_fd);
void	change_stdout_to_pipe(int *pipe_fd);

// inlim/children.c
void	just_one_cmd(char **cmd, char **envp);
void	first_cmd(int (*pipe_fd)[2], char **cmd, char **envp);
void	middle_cmd(int pid_index, int (*pipe_fd)[2], char **cmd, char **envp);
void	last_cmd(int pid_index, int (*pipe_fd)[2], char **cmd, char **envp);
void	child(int pid_index, int last_pid_index, int (*pipe_fd)[2], char **cmd, char **envp);

// inlim/execute.c
int		process_count(t_list *lst);
int		size_count(t_list *lst);
char	**make_cmd(t_list **lst, int size);
int		**pipe_malloc(int pipe_count);
void	connect_pipe(t_vars *vars, pid_t *pid, int process, char **path);
void	execute(t_vars *vars);
char	*path_join(char **path, char *cmd);
int		builtin_fuc(t_vars *vars);

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

#endif
