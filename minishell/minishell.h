#ifndef MINISHELL_H
# define MINISHELL_H

enum	e_quote
{
	SINGLE = 0,
	DOUBLE,
};

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

void	split_by_pipe(char *str);

#endif
