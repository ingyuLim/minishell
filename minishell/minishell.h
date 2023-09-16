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
void	execute(t_list *lst, char *envp[]);

// seunan/cd.c
void	cd(t_list *cmd);

// seunan/pwd.c
void	pwd(void);

// seunan/echo.c
void	echo(t_list *cmd);

#endif
