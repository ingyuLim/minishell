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

// execute.c
void	builtin_fuc(t_vars *vars, t_list *lst);
void	execute(t_vars *vars);

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

#endif
