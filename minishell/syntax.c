#include "minishell.h"

/*
static char	test_state[8][20] = {
	"START",				// 명령어의 시작
	"CMD",
	"FNAME",
	"PIPE",					// |
	"IN_REDIR",				// <
	"OUT_REDIR",			// >
	"HEREDOC",				// << limiter
	"PAIR_OUT_REDIR",		// >>
};
*/

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

int	is_word(t_state state)
{
	if (state == CMD || state == FNAME)
		return (1);
	return (0);
}

int	syntax_check(t_list *lst)
{
	t_state	current_state;

	current_state = START;
	while (lst != NULL)
	{
		if (ft_strncmp(lst->token, "|", 2) == 0)
		{
			if (!is_word(current_state))
			{
				print_red("minishell: syntax error near unexpected token");
				return (1);
			}
			current_state = PIPE;
			lst->state = PIPE;
		}
		else if (ft_strncmp(lst->token, "<", 2) == 0)
		{
			if (!is_word(current_state) && current_state != PIPE && current_state != START)
			{
				print_red("minishell: syntax error near unexpected token");
				return (1);
			}
			current_state = IN_REDIR;
			lst->state = IN_REDIR;
		}
		else if (ft_strncmp(lst->token, ">", 2) == 0)
		{
			if (!is_word(current_state) && current_state != PIPE && current_state != START)
			{
				print_red("minishell: syntax error near unexpected token");
				return (1);
			}
			current_state = OUT_REDIR;
			lst->state = OUT_REDIR;
		}
		else if (ft_strncmp(lst->token, "<<", 3) == 0)
		{
			if (!is_word(current_state) && current_state != PIPE && current_state != START)
			{
				print_red("minishell: syntax error near unexpected token");
				return (1);
			}
			current_state = HEREDOC;
			lst->state = HEREDOC;
		}
		else if (ft_strncmp(lst->token, ">>", 3) == 0)
		{
			if (!is_word(current_state) && current_state != PIPE && current_state != START)
			{
				print_red("minishell: syntax error near unexpected token");
				return (1);
			}
			current_state = PAIR_OUT_REDIR;
			lst->state = PAIR_OUT_REDIR;
		}
		else
		{
			if (current_state == START || current_state == PIPE || current_state == CMD || current_state == FNAME)
			{
				current_state = CMD;
				lst->state = CMD;
			}
			else
			{
				current_state = FNAME;
				lst->state = FNAME;
			}
		}
		// printf("%s, %s\n", lst->token, test_state[current_state]);
		lst = lst->next;
	}
	if (current_state == START || !is_word(current_state))
	{
		if (current_state != START)
			print_red("minishell: syntax error near unexpected token");
		return (1);
	}
	return (0);
}
