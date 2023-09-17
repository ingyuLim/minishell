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
				print_red("minishell: syntax error near unexpected token");
				return (1);
			}
			current_state = PIPE;
		}
		else if (ft_strncmp(tmp->token, "<", 2) == 0)
		{
			if (current_state != WORD && current_state != PIPE && current_state != START)
			{
				print_red("minishell: syntax error near unexpected token");
				return (1);
			}
			current_state = IN_REDIRECT;
		}
		else if (ft_strncmp(tmp->token, ">", 2) == 0)
		{
			if (current_state != WORD && current_state != PIPE && current_state != START)
			{
				print_red("minishell: syntax error near unexpected token");
				return (1);
			}
			current_state = OUT_REDIRECT;
		}
		else if (ft_strncmp(tmp->token, "<<", 3) == 0)
		{
			if (current_state != WORD && current_state != PIPE && current_state != START)
			{
				print_red("minishell: syntax error near unexpected token");
				return (1);
			}
			current_state = DOUBLE_IN_REDIRECT;
		}
		else if (ft_strncmp(tmp->token, ">>", 3) == 0)
		{
			if (current_state != WORD && current_state != PIPE && current_state != START)
			{
				print_red("minishell: syntax error near unexpected token");
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
	if (current_state == START)
	{
		return (1);
	}
	if (current_state != WORD)
	{
		print_red("minishell: syntax error near unexpected token");
		return (1);
	}
	// print_green("Valid syntax");
	return (0);
}
