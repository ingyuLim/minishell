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

// minishell.c
void	minishell(t_vars *vars);

// syntax.c
int		syntax_check(t_list *lst);
int		is_valid_one(t_list *lst, t_state *cur);
int		is_valid_two(t_list *lst, t_state *cur);

// syntax_utils.c
int		is_word(t_state state);
void	change_state(t_state *cur, t_state *lst, t_state state);
int		last_condition(t_list *lst);

// utils.c
void	init_vars(t_vars *vars, char *envp[]);
void	free_vars(t_vars *vars, int a, char *b[]);
void	free_str_tok(char *str, t_list **lst);

// error.c
void	error(char *err, char *cmd);
void	exit_with_err(char *err, char *cmd);
void	error_msg(char *msg, char *cmd, char *arg);
void	exit_with_msg(char *msg, char *cmd, char *arg);

// env.c
void	trim_quote_and_replace_env(t_vars *vars);
void	meet_single_quote(char **result, char *content, int *i);
void	meet_double_quote(char **result, char *content, int *i, t_env *env);
int		quotes_check(char *str);
char	*replace_env_vars(char *content, t_env *env);
void	state_join(char **result, int *i);
void	env_join(char *content, char **result, int *i, t_env *env);
int		is_valid_quotes(char *str);

// env_utils.c
int		is_envvar(char *content, int i);
int		is_state(char *content, int i);
char	*find_env(char *key, t_env *env);
char	*ft_strjoin_char(char *s1, char c);

// signal.c
void	sigint_handler(int signo);
void	sigquit_handler(int signo);

// parse.c
char	*meet_quote(char *str, int *i, char quote);
char	*meet_sep(char *str, int *i);
char	*make_word(char *str, int *i);
char	*make_symbol(char *str, char c, int *i);
t_list	*tokenize(char *str);

// builtin_utils.c
int		ft_isvalidkey(char *key);
t_env	*ft_envlast(t_env *env);
void	ft_envadd_back(t_env **head, t_env *new);
t_env	*make_env(char *content);
t_env	*dup_env(char *envp[]);

// builtin/*.c
int		b_cd(char **cmd);
int		b_echo(char **cmd);
int		b_pwd(void);
int		b_exit(char **cmd);
int		is_num(char *str);
int		b_env(char **cmd, t_env *env);
int		b_export(char **cmd, t_env *env);
void	print_env(t_env *env);
void	add_env(t_env *env, char *cmd);
int		b_unset(char **cmd, t_env **env);
void	change_head(char *cmd, t_env **env);
void	delete_node(char *cmd, t_env *env);

// test/test.c
void	leak(void);
void	print_tokens(t_list *lst);

// execute/execute.c
int		process_count(t_list *lst);
int		cmd_size_count(t_list *lst);
int		count_cmd_count(t_list *lst);
char	**make_cmd(t_list *lst);
char	**make_envp(t_env *env);
char	*path_join(char **path, char *cmd);
void	free_envp(char **envp);
void	move_next_syntax(t_list **lst, int *tmp_arr_index);
void	find_redirect(t_list *lst, char **tmp_arr, int tmp_arr_index);
char	**malloc_tmp_arr(t_list *lst);
int		exist_nl(char *buf);
size_t	gnl_strlen(char *str);
void	free_tmp_arr(char **tmp_arr);
void	fill_tmp_arr(char *tmp_file, char **tmp_arr, t_list *lst);
int		ft_is_redirection(t_list *lst);
void	connect_pipe(t_vars *vars, pid_t *pid, int process, char **path);
int		is_builtin(char **cmd);
int		builtin_func(t_vars *vars, char **cmd);
char	**parse_path(t_env *env);
void	free_path(char **path);
char	*find_env(char *key, t_env *env);
char	*ft_strjoin_char(char *s1, char c);
char	*replace_env_vars(char *content, t_env *env);
void	execute(t_vars *vars);

// execute/change_in_and_out.c
void	change_stdin_to_pipe(int *pipe_fd);
void	change_stdout_to_pipe(int *pipe_fd);

// execute/children.c
void	first_cmd(int (*pipe_fd)[2]);
void	middle_cmd(int pid_index, int (*pipe_fd)[2]);
void	last_cmd(int pid_index, int (*pipe_fd)[2]);

// execute/use_function1.c
void	use_execve(char *path, char *argv[], char *envp[]);
void	use_pipe(int *fd);
pid_t	use_fork(void);
void	use_free(void *mem);

// execute/use_function2.c
pid_t	use_waitpid(pid_t pid, int *stat_loc, int options);
void	use_dup2(int fd1, int fd2);
void	use_close(int fd);
int		infile_open(const char *path, int oflag);

#endif
