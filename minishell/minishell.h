#ifndef MINISHELL_H
# define MINISHELL_H

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

void	minishell(char *str);

#endif
