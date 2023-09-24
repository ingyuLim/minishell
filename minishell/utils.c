#include "minishell.h"

void	init_vars(t_vars *vars, char *envp[])
{
	vars->env = dup_env(envp);
	vars->lst = NULL;
}

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

void	free_str_tok(char *str, t_list **lst)
{
	free(str);
	ft_lstclear(lst, free);
}
