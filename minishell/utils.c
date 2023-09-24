#include "minishell.h"

void	init_vars(t_vars *vars, char *envp[])
{
	vars->env = dup_env(envp);
	vars->lst = NULL;
}

void	free_vars(t_vars *vars, int a, char *b[])
{
	t_env	*e_tmp;
	(void) a;
	(void) b;

	while (vars->env != NULL)
	{
		e_tmp = vars->env;
		free(e_tmp->key);
		free(e_tmp->value);
		vars->env = vars->env->next;
		free(e_tmp);
	}
	free(vars);
}

void	free_str_tok(char *str, t_list **lst)
{
	free(str);
	ft_lstclear(lst, free);
}
