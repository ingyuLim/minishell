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

/* syntax.c */

// 유한 오토마타의 상태 열거형
typedef enum	e_state{
	START,					// 명령어의 시작
	PIPE,					// |
	IN_REDIRECT,			// <
	OUT_REDIRECT,			// >
	WORD,					// command or argument or file name
	DOUBLE_IN_REDIRECT,		// <<
	DOUBLE_OUT_REDIRECT,	// >>
	OPEN_PAREN,				// (
	CLOSE_PAREN,			// )
	AND_OPERATOR,			// &&
	OR_OPERATOR				// ||
} t_state;

typedef enum	e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

/* syntax.c */

// utils.c
void	exit_with_msg(char *msg);
int		ft_issymbol(char c);
int		ft_isseparator(char c);
int		ft_isword(char c);

// parse.c
char	*meet_quote(char *str, int *i, char quote);
char	*meet_sep(char *str, int *i);
char	*make_word(char *str, int *i);
char	*make_symbol(char *str, char c, int *i);
t_list	*tokenize(char *str);

void	print(t_list *lst);

// syntax.c
int	syntax_check(t_list *head);

#endif
