#include "minishell.h"

typedef enum	e_state{
	START,					// 명령어의 시작
	PIPE,					// |
	IN_REDIRECT,			// <
	OUT_REDIRECT,			// >
	WORD,					// command or argument or file name
	DOUBLE_IN_REDIRECT,		// <<
	DOUBLE_OUT_REDIRECT,	// >>
} t_state;

void	print_green(char *str)
{
	printf("\033[1;32m");
	printf("%s\n", str);
	printf("\033[0m");
}

void	print_red(char *str)
{
	printf("\033[1;31m");
	printf("%s\n", str);
	printf("\033[0m");
}

int	syntax_check(t_list *head)
{
	t_list	*tmp;
	t_state	current_state;

	tmp = head;
	current_state = START;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->token, "|", 2) == 0)
		{
			if (current_state != WORD)
			{
				print_red("Invalid syntax");
				return (1);
			}
			current_state = PIPE;
		}
		else if (ft_strncmp(tmp->token, "<", 2) == 0)
		{
			if (current_state != WORD && current_state != PIPE && current_state != START)
			{
				print_red("Invalid syntax");
				return (1);
			}
			current_state = IN_REDIRECT;
		}
		else if (ft_strncmp(tmp->token, ">", 2) == 0)
		{
			if (current_state != WORD && current_state != PIPE && current_state != START)
			{
				print_red("Invalid syntax");
				return (1);
			}
			current_state = OUT_REDIRECT;
		}
		else if (ft_strncmp(tmp->token, "<<", 2) == 0)
		{
			if (current_state != WORD && current_state != PIPE && current_state != START)
			{
				print_red("Invalid syntax");
				return (1);
			}
			current_state = DOUBLE_IN_REDIRECT;
		}
		else if (ft_strncmp(tmp->token, ">>", 2) == 0)
		{
			if (current_state != WORD && current_state != PIPE && current_state != START)
			{
				print_red("Invalid syntax");
				return (1);
			}
			current_state = DOUBLE_OUT_REDIRECT;
		}
		else
		{
			current_state = WORD;
		}
		tmp = tmp->next;
	}
	if (current_state == PIPE ||
		current_state == IN_REDIRECT ||
		current_state == OUT_REDIRECT ||
		current_state == DOUBLE_IN_REDIRECT ||
		current_state == DOUBLE_OUT_REDIRECT)
	{
		print_red("WORD must appear after the pipe or redirect");
		return (1);
	}
	print_green("Valid syntax");
	return (0);
}
