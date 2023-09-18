#include "minishell.h"

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
			lst->state = PIPE;
			current_state = PIPE;
		}
		else if (ft_strncmp(lst->token, "<", 2) == 0)
		{
			if (!is_word(current_state) && current_state != PIPE && current_state != START)
			{
				print_red("minishell: syntax error near unexpected token");
				return (1);
			}
			lst->state = IN_REDIR;
			current_state = IN_REDIR;
		}
		else if (ft_strncmp(lst->token, ">", 2) == 0)
		{
			if (!is_word(current_state) && current_state != PIPE && current_state != START)
			{
				print_red("minishell: syntax error near unexpected token");
				return (1);
			}
			lst->state = OUT_REDIR;
			current_state = OUT_REDIR;
		}
		else if (ft_strncmp(lst->token, "<<", 3) == 0)
		{
			if (!is_word(current_state) && current_state != PIPE && current_state != START)
			{
				print_red("minishell: syntax error near unexpected token");
				return (1);
			}
			lst->state = PAIR_IN_REDIR;
			current_state = PAIR_IN_REDIR;
		}
		else if (ft_strncmp(lst->token, ">>", 3) == 0)
		{
			if (!is_word(current_state) && current_state != PIPE && current_state != START)
			{
				print_red("minishell: syntax error near unexpected token");
				return (1);
			}
			lst->state = PAIR_OUT_REDIR;
			current_state = PAIR_OUT_REDIR;
		}
		else
		{
			if (current_state == START || current_state == PIPE)
			{
				lst->state = CMD;
				current_state = CMD;
			}
			else
			{
				lst->state = FNAME;
				current_state = FNAME;
			}
		}
		lst = lst->next;
	}
	if (current_state == START || !is_word(current_state))
	{
		print_red("minishell: syntax error near unexpected token");
		return (1);
	}
	return (0);
}
