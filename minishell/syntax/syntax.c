#include "../minishell.h"

int	syntax_check(t_list *lst)
{
	t_state	cur;

	cur = START;
	while (lst != NULL)
	{
		if (!(is_valid_one(lst, &cur) && is_valid_two(lst, &cur)))
		{
			error_msg("syntax error near unexpected token", 0, 0);
			return (0);
		}
		lst = lst->next;
	}
	if (cur == START || !is_word(cur))
	{
		if (cur != START)
			error_msg("syntax error near unexpected token", 0, 0);
		return (0);
	}
	return (1);
}

int	is_valid_one(t_list *lst, t_state *cur)
{
	int	flag;

	flag = 0;
	if (ft_strncmp(lst->token, "|", 2) == 0)
	{
		if (!is_word(*cur))
			flag = 1;
		change_state(cur, &(lst->state), PIPE);
	}
	else if (ft_strncmp(lst->token, "<", 2) == 0)
	{
		if (!is_word(*cur) && *cur != PIPE && *cur != START)
			flag = 1;
		change_state(cur, &(lst->state), IN_REDIR);
	}
	else if (ft_strncmp(lst->token, ">", 2) == 0)
	{
		if (!is_word(*cur) && *cur != PIPE && *cur != START)
			flag = 1;
		change_state(cur, &(lst->state), OUT_REDIR);
	}
	if (flag)
		return (0);
	return (1);
}

int	is_valid_two(t_list *lst, t_state *cur)
{
	int	flag;

	flag = 0;
	if (ft_strncmp(lst->token, "<<", 3) == 0)
	{
		if (!is_word(*cur) && *cur != PIPE && *cur != START)
			flag = 1;
		change_state(cur, &(lst->state), HEREDOC);
	}
	else if (ft_strncmp(lst->token, ">>", 3) == 0)
	{
		if (!is_word(*cur) && *cur != PIPE && *cur != START)
			flag = 1;
		change_state(cur, &(lst->state), PAIR_OUT_REDIR);
	}
	else if (last_condition(lst))
	{
		if (*cur == START || *cur == PIPE || *cur == CMD || *cur == FNAME)
			change_state(cur, &(lst->state), CMD);
		else
			change_state(cur, &(lst->state), FNAME);
	}
	if (flag)
		return (0);
	return (1);
}
