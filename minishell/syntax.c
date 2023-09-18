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
			if (is_word(current_state) == 0)
			{
				print_red("minishell: syntax error near unexpected token");
				return (1);
			}
			tmp->state = PIPE;
			current_state = PIPE;
		}
		else if (ft_strncmp(tmp->token, "<", 2) == 0)
		{
			if (is_word(current_state) == 0 && current_state != PIPE && current_state != START)
			{
				print_red("minishell: syntax error near unexpected token");
				return (1);
			}
			tmp->state = IN_REDIR;
			current_state = IN_REDIR;
		}
		else if (ft_strncmp(tmp->token, ">", 2) == 0)
		{
			if (is_word(current_state) == 0 && current_state != PIPE && current_state != START)
			{
				print_red("minishell: syntax error near unexpected token");
				return (1);
			}
			tmp->state = OUT_REDIR;
			current_state = OUT_REDIR;
		}
		else if (ft_strncmp(tmp->token, "<<", 3) == 0)
		{
			if (is_word(current_state) == 0 && current_state != PIPE && current_state != START)
			{
				print_red("minishell: syntax error near unexpected token");
				return (1);
			}
			tmp->state = PAIR_IN_REDIR;
			current_state = PAIR_IN_REDIR;
		}
		else if (ft_strncmp(tmp->token, ">>", 3) == 0)
		{
			if (is_word(current_state) == 0 && current_state != PIPE && current_state != START)
			{
				print_red("minishell: syntax error near unexpected token");
				return (1);
			}
			tmp->state = PAIR_OUT_REDIR;
			current_state = PAIR_OUT_REDIR;
		}
		else
		{
			if (current_state == START || current_state == PIPE)
				tmp->state = CMD;
			else
				tmp->state = FNAME;
		}
		tmp = tmp->next;
	}
	if (current_state == START)
		return (1);
	if (is_word(current_state) == 0)
	{
		print_red("minishell: syntax error near unexpected token");
		return (1);
	}
	return (0);
}
