#ifndef MINISHELL_H
# define MINISHELL_H

enum e_quote
{
	SINGLE = 0,
	DOUBLE = 1
};
# define TRUE 1;
# define FALSE 0;
# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'
# include "./libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <term.h>
# include <termios.h>

#endif
