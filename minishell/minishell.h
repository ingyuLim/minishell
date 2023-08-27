#ifndef MINISHELL_H
# define MINISHELL_H

enum e_quote
{
	SINGLE = 0,
	DOUBLE,
};

# include "./libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <term.h>
# include <termios.h>

#endif
