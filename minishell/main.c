#include "minishell.h"

void	free_vars(t_vars *vars, int a, char *b[])
{
	t_env	*tmp;
	(void) a;
	(void) b;

	while (vars->env != NULL)
	{
		tmp = vars->env;
		free(tmp->key);
		free(tmp->value);
		vars->env = vars->env->next;
		free(tmp);
	}
	free(vars);
}

int	main(int argc, char *argv[], char *envp[])
{
	atexit(leak);
	t_vars	*vars;
	char	*str;

	vars = (t_vars *)ft_calloc(1, sizeof(t_vars));
	vars->env = dup_env(envp);
	while (1)
	{
		str = readline("\033[0;36mminishell$\033[0m ");
		if (str == NULL)
		{
			printf("exit\n");
			break ;
		}
		vars->lst = tokenize(str);
		if (syntax_check(vars->lst) == 1)
		{
			free_strtok(str, &(vars->lst));
			continue ;
		}
		add_history(str);
		// print_tokens(vars->lst);
		execute(vars);
		free_strtok(str, &(vars->lst));
	}
	free_vars(vars, argc, argv);
	return (g_status);
}
// USER=test | env | grep USER => 환경변수 변경 적용 안되는게 맞나?

// "g"r"epadasdasfasd"
