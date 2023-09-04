#include "minishell.h"

int	main(void)
{
	char	*str;

	while (1)
	{
		str = readline("\033[0;36mminishell$\033[0m ");
		if (ft_strncmp(str, "exit", 5) == 0)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		print(parse(str));
		add_history(str);
		free(str);
	}
	return (0);
}
