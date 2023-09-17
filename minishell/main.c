#include "minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env != NULL)
	{
		tmp = env;
		free(tmp->key);
		free(tmp->value);
		env = env->next;
		free(tmp);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	atexit(leak);
	t_vars	*vars;
	char	*str;

	vars = (t_vars *)ft_calloc(1, sizeof(t_vars));
	vars->env = dup_env(envp);
	while (1)
	{
		str = readline("\033[0;36mminishell$\033[0m ");
		if (ft_strncmp(str, "exit", 5) == 0)
		{
			free(str);
			ft_putstr_fd("exit\n", 1);
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
	free_env(vars->env);
	return (0);
}
// USER=test | env | grep USER => 환경변수 변경 적용 안되는게 맞나?

// "g"r"epadasdasfasd"
