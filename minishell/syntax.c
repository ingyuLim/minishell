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
				printf("\033[1;31m");
				printf("Invalid syntax.\n");
				printf("\033[0m");
				return (1);
			}
			current_state = PIPE;
		}
		else if (ft_strncmp(tmp->token, "<", 2) == 0 ||
					ft_strncmp(tmp->token, ">", 2) == 0 ||
					ft_strncmp(tmp->token, "<<", 3) == 0 ||
					ft_strncmp(tmp->token, ">>", 3) == 0)
		{
			if (current_state != WORD)
			{
				printf("\033[1;31m");
				printf("Invalid syntax\n");
				printf("\033[0m");
				return (1);
			}
			current_state = IN_REDIRECT;
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
		printf("WORD must appear after the pipe or redirect\n");
		return (1);
	}
	printf("\033[1;32m");
	printf("Valid syntax\n");
	printf("\033[1;32m");
	return (0);
}
