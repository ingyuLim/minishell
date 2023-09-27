#include "../minishell.h"

int	is_word(t_state state)
{
	if (state == CMD || state == FNAME)
		return (1);
	return (0);
}

void	change_state(t_state *cur, t_state *lst, t_state state)
{
	*cur = state;
	*lst = state;
}

int	last_condition(t_list *lst)
{
	if (ft_strncmp(lst->token, "|", 2) != 0
		&& ft_strncmp(lst->token, "<", 2) != 0
		&& ft_strncmp(lst->token, ">", 2) != 0)
		return (1);
	return (0);
}
