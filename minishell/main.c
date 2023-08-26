#include "minishell.h"

int	main(void)
{
	char	*str;

	while (1)
	{
		str = readline("\033[0;37mminishell$\033[0;31m>\033[0;m ");
		if (ft_strncmp(str, "exit", 5) == 0)
			break ;
		else
			minishell(str);
		add_history(str);
		free(str);
	}
	return (0);
}
