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

// parse.c
void	exit_with_msg(char *msg);
int		ft_issymbol(char c);
int		ft_isseparator(char c);
int		ft_isword(char c);
char	*meet_quote(char *str, int *i, char quote);
char	*meet_sep(char *str, int *i);
char	*make_word(char *str, int *i);
char	*make_symbol(char *str, int *i);
t_list	*tokenize(char *str);

void	print(t_list *lst);

#endif
