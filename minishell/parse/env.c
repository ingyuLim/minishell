#include "../minishell.h"

void	trim_quote_and_replace_env(t_vars *vars)
{
	t_list	*lst;
	char	*mem;

	lst = vars->lst;
	while (lst != NULL)
	{
		mem = lst->token;
		lst->token = replace_env_vars(lst->token, vars->env);
		free(mem);
		lst = lst->next;
	}
}

int	quotes_check(char *str)
{
	if (is_valid_quotes(str) == 0)
	{
		use_free(str);
		error_msg("Invalid quotes", 0, 0);
		return (0);
	}
	return (1);
}

void	meet_single_quote(char **result, char *content, int *i)
{
	char	*tmp;
	char	*mem;
	int		start;
	int		len;

	++(*i);
	start = *i;
	len = 0;
	while(content[*i] != '\0' && content[*i] != '\'')
	{
		++len;
		++(*i);
	}
	++(*i);	// 따옴표 다음 인덱스
	tmp = ft_substr(content, start, len);
	mem = *result;
	*result = ft_strjoin(*result, tmp);
	use_free(mem);
	use_free(tmp);
}

void	meet_double_quote(char **result, char *content, int *i, t_env *env)
{
	char	*tmp;
	char	*mem;
	int		start;
	int		len;

	++(*i);
	start = *i;
	len = 0;
	while(content[*i] != '\0' && content[*i] != '\"')
	{
		if (is_envvar(content, *i))
		{
			if (is_state(content, *i))
				state_join(result, i);
			else
				env_join(content, result, i, env);
		}
		++len;
		++(*i);
	}
	++(*i);	// 따옴표 다음 인덱스
	tmp = ft_substr(content, start, len);
	mem = *result;
	*result = ft_strjoin(*result, tmp);
	use_free(mem);
	use_free(tmp);
}

char	*replace_env_vars(char *content, t_env *env)
{
	char	*result;
	int		i;

	(void) env;
	result = ft_strdup("");
	i = 0;
	while (content[i] != '\0')
	{
		if (content[i] == '\'')
			meet_single_quote(&result, content, &i);
		else if (content[i] == '\"')
			meet_double_quote(&result, content, &i, env);
		else if (is_envvar(content, i))
		{
			if (is_state(content, i))
				state_join(&result, &i);
			else
				env_join(content, &result, &i, env);
		}
		else
		{
			result = ft_strjoin_char(result, content[i]);
			++i;
		}
	}
	return (result);
}

// char	*replace_env_vars(char *content, t_env *env)
// {
// 	char	*result;
// 	int		i;
// 	int		flag;

// 	result = ft_strdup("");
// 	i = 0;
// 	flag = 0;
// 	while (content[i] != '\0')
// 	{
// 		if (content[i] == '\'')
// 			flag = !flag;
// 		if (is_envvar(content, i, flag))
// 		{
// 			if (is_state(content, i))
// 				state_join(&result, &i);
// 			else
// 				env_join(content, &result, &i, env);
// 		}
// 		else
// 		{
// 			result = ft_strjoin_char(result, content[i]);
// 			++i;
// 		}
// 	}
// 	return (result);
// }

void	state_join(char **result, int *i)
{
	char	*tmp;

	tmp = *result;
	*result = ft_strjoin(*result, ft_itoa(g_status));
	use_free(tmp);
	*i += 2;
}

void	env_join(char *content, char **result, int *i, t_env *env)
{
	int		j;
	char	*tmp;
	char	*key;

	j = *i + 1;
	while (content[j] != '\0' && !ft_iswhitespace(content[j]) && !ft_isquote(content[j]) && content[j] != '$')
		j++;
	key = ft_substr(content, *i + 1, j - *i - 1);
	tmp = *result;
	*result = ft_strjoin(*result, find_env(key, env));
	use_free(tmp);
	use_free(key);
	*i = j;
}

int	is_valid_quotes(char *str)
{
	int	i;
	int	sin;
	int	dou;

	i = 0;
	sin = 0;
	dou = 0;
	while (str[i])
	{
		if (str[i] == '\'' && dou % 2 == 0)
			sin++;
		else if (str[i] == '\"' && sin % 2 == 0)
			dou++;
		i++;
	}
	if (sin % 2 == 0 && dou % 2 == 0)
		return (1);
	return (0);
}
