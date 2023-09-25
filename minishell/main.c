#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	// atexit(leak);
	t_vars	*vars;

	vars = (t_vars *)ft_calloc(1, sizeof(t_vars));
	init_vars(vars, envp);
	minishell(vars);
	free_vars(vars, argc, argv);
	return (g_status);
}
