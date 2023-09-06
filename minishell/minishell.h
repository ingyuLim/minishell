#ifndef MINISHELL_H
# define MINISHELL_H

enum e_type
{
	WORD = 0,
	PIPE = 1,
	SEMICOLON = 2,
	REDIRECT = 3,
};

# include "./libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <term.h>
# include <termios.h>

void	print(t_list *lst);
void	add_token(t_list *lst, char *str, int *i);
t_list	*parse(char *str);

#endif
