#include "../minishell.h"

t_env	*ft_envlast(t_env *env)
{
	if (env == NULL)
		return (NULL);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

void	ft_envadd_back(t_env **head, t_env *new)
{
	t_env	*tmp;

	if (new == NULL)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	tmp = ft_envlast(tmp);
	tmp->next = new;
}

t_env	*make_env(char *contents)
{
	t_env	*env;
	char	*tmp;
	char	*cut;

	tmp = ft_strdup(contents);
	env = (t_env *)ft_calloc(1, sizeof(t_env));
	cut = ft_strchr(tmp, '=');
	env->value = ft_strdup(cut + 1);
	*cut = '\0';
	env->key = ft_strdup(tmp);
	env->next = NULL;
	free(tmp);
	return (env);
}

t_env	*dup_env(char *envp[])
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		ft_envadd_back(&env, make_env(envp[i]));
		++i;
	}
	return (env);
}

int	b_cd(t_list *lst)
{
	char	*path;

	lst = lst->next;
	if (lst == NULL || ft_strncmp(lst->token, "~", 2) == 0)
	{
		printf("HOME: %s\n", getenv("USER"));
		path = getenv("HOME");
	}
	else
		path = lst->token;
	printf("path: %s\n", path);
	if (chdir(path) == -1)
	{
		error(path);
		return (1);
	}
	return (0);
}

int	b_pwd(void)
{
	char *path;

	path = getcwd(NULL, BUFSIZ);
	printf("%s\n", path);
	free(path);
	return (0);
}

int	b_echo(t_list *lst)
{
	int	flag;

	flag = 0;
	lst = lst->next;
	if(lst != NULL && ft_strncmp("-n", lst->token, 3) == 0)
	{
		lst = lst->next;
		flag = 1;
	}
	while(lst != NULL)
	{
		ft_putstr_fd(lst->token, 1);
		if(lst->next != NULL)
			ft_putchar_fd(' ', 1);
		lst = lst->next;
	}
	if(flag == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}

int	b_export(t_list *lst, t_env *env)
{
	lst = lst->next;
	if (lst == NULL)
	{
		while (env != NULL)
		{
			ft_putstr_fd(env->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(env->value, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			env = env->next;
		}
	}
	return (0);
}

int	b_env(t_list *lst, t_env *env)
{
	lst = lst->next;
	if (lst == NULL)
	{
		while (env != NULL)
		{
			ft_putstr_fd(env->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(env->value, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			env = env->next;
		}
	}
	return (0);
}

int	b_exit(t_list *lst)
{
	lst = lst->next;
	if (lst == NULL)
		exit(0);
	exit(ft_atoi(lst->token));
}

int	ft_isspecialtok(char *s)
{
	if (ft_strncmp(s, "|", 2) == 0)
		return (1);
	else if (ft_strncmp(s, ">", 2) == 0)
		return (1);
	else if (ft_strncmp(s, ">>", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "<", 2) == 0)
		return (1);
	else if (ft_strncmp(s, "<<", 3) == 0)
		return (1);
	return (0);
}

int	b_unset(t_list **lst, t_env *env)
{
	t_env	*enode;
	t_env	*prev;
	t_env	*tmp;

	*lst = (*lst)->next;
	while (*lst != NULL && ft_isspecialtok((*lst)->token) == 0)
	{
		enode = env;
		while (enode != NULL)
		{
			if (ft_strncmp(tmp->key, (*lst)->token, ft_strlen((*lst)->token)) == 0)
			{
				free(tmp->key);
				free(tmp->value);
				tmp->key = NULL;
				tmp->value = NULL;
			}
			enode = enode->next;
		}
		*lst = (*lst)->next;
	}
}
