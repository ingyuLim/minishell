/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:00:48 by seunan            #+#    #+#             */
/*   Updated: 2023/10/04 01:01:12 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int					g_status;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_vars
{
	t_list				*lst;
	t_env				*env;
	struct sigaction	act;
	struct sigaction	oact_int;
	struct sigaction	oact_quit;
}					t_vars;

typedef struct s_execute
{
	int				pid_index;
	char			**tmp_arr;
	int				tmp_arr_index;
	char			**envp;
	char			**cmd;
}					t_execute;

void				minishell(t_vars *vars);

// utils.c
void				init_vars(t_vars *vars, char *envp[]);
void				free_vars(t_vars *vars, int a, char *b[]);
void				free_str_tok(char *str, t_list **lst);

// signal.c
void				signal_action(t_vars *vars);
void				sigint_handler(int signo);
void				sigint_handler_exec(int signum);

// error.c
void				error(char *err, char *cmd);
void				exit_with_err(char *err, char *cmd, int status);
void				error_msg(char *msg, char *cmd, char *arg);
void				exit_with_msg(char *msg, char *cmd, char *arg);

// syntax.c
int					syntax_check(t_list *lst);
int					is_valid_one(t_list *lst, t_state *cur);
int					is_valid_two(t_list *lst, t_state *cur);

// syntax_utils.c
int					is_word(t_state state);
void				change_state(t_state *cur, t_state *lst, t_state state);
int					last_condition(t_list *lst);

// parse.c
t_list				*tokenize(char *str);
char				*make_symbol(char *str, char c, int *i);
char				*make_word(char *str, int *i);
char				*meet_quote(char *str, int *i, char quote);
char				*meet_sep(char *str, int *i);

// env_vars.c
void				replace_env_and_trim_quote(t_vars *vars);
char				*replace_env_vars(char *content, t_env *env);
void				meet_single_quote(char **result, char *content, int *i);
void				meet_double_quote(char **result, char *content, int *i,
						t_env *env);

// env_join.c
void				state_join(char **result, int *i);
void				env_join(char *content, char **result, int *i, t_env *env);
char				*ft_strjoin_char(char *s1, char c);

// env_utils.c
int					is_envvar(char *content, int i);
int					is_state(char *content, int i);
int					is_valid_quotes(char *str);
char				*find_env(char *key, t_env *env);
int					quotes_check(char *str);

// builtin_utils.c
int					ft_isvalidkey(char *key);
t_env				*ft_envlast(t_env *env);
void				ft_envadd_back(t_env **head, t_env *new);
t_env				*make_env(char *content);
t_env				*dup_env(char *envp[]);

// cd.c
int					b_cd(char **cmd);

// echo.c
int					b_echo(char **cmd);

// pwd.c
int					b_pwd(void);

// exit.c
int					b_exit(char **cmd);
int					is_num(char *str);

// env.c
int					b_env(t_env *env);

// export.c
int					b_export(char **cmd, t_env **env);
int					add_env(t_env **env, char *cmd);
void				print_env(t_env *env, int flag);
int					ft_isvalidenv(t_env **env, char *cmd, t_env *e_tmp);
void				print_quote(int flag);

// unset.c
int					b_unset(char **cmd, t_env **env);
void				change_head(char *cmd, t_env **env);
void				delete_node(char *cmd, t_env *env);

// test/test.c
void				leak(void);
void				print_tokens(t_list *lst);

// execute/execute.c
int					process_count(t_list *lst);
int					cmd_size_count(t_list *lst);
int					count_cmd_count(t_list *lst);
char				**make_cmd(t_list *lst);
char				**make_envp(t_env *env);
char				*path_join(char **path, char *cmd);
void				free_envp(char **envp);
void				move_next_syntax(t_list **lst, int (*pipe_fd)[2],
						int *tmp_arr_index, int *pid_index);
void				find_in_redir(t_list **lst);
void				find_out_redir(t_list **lst);
void				find_heredoc(char **tmp_arr, int tmp_arr_index);
void				find_pair_out_redir(t_list **lst);
void				find_redirect(t_list *lst, char **tmp_arr,
						int tmp_arr_index);
char				**malloc_tmp_arr(t_list *lst);
size_t				gnl_strlen(char *str);
char				*naming_tmp_file(char *tmp_file);
void				write_in_tmpfile(t_list *lst, int tmp_fd);
void				fill_tmp_arr(char **tmp_arr, t_list *lst);
int					ft_is_redirection(t_list *lst);
void				free_tmp_arr(char **tmp_arr);
void				execute_command(t_vars *vars, char **cmd, char **envp);
void				clear_resources(char **envp, int process, int (*pipe_fd)[2],
						char **tmp_arr);
void				close_last_pipe(int (*pipe_fd)[2], int pid_index);
void				init_variable(t_vars *vars, t_list **lst, t_execute *data);
void				execute(t_vars *vars, pid_t *pid, int (*pipe_fd)[2],
						int process);
int					ft_onlybuiltin(t_execute data, t_list *lst, int process);
int					is_builtin(char **cmd);
int					builtin_func(t_vars *vars, char **cmd);
char				**parse_path(t_env *env);
void				free_path(char **path);
void				execute_frame(t_vars *vars);
void				wait_child(pid_t *pid, int process);

// execute/change_in_and_out.c
void				change_stdin_to_pipe(int *pipe_fd);
void				change_stdout_to_pipe(int *pipe_fd);

// execute/connect_pipe.c
void				first_cmd(int (*pipe_fd)[2]);
void				middle_cmd(int pid_index, int (*pipe_fd)[2]);
void				last_cmd(int pid_index, int (*pipe_fd)[2]);
void				connect_pipe(int pid_index, int process, int (*pipe_fd)[2]);

// execute/use_function1.c
void				use_execve(char *path, char *argv[], char *envp[]);
void				use_pipe(int *fd);
pid_t				use_fork(void);
void				use_free(void *mem);

// execute/use_function2.c
pid_t				use_waitpid(pid_t pid, int *stat_loc, int options);
void				use_dup2(int fd1, int fd2);
void				use_close(int fd);
int					infile_open(const char *path, int oflag);

#endif
