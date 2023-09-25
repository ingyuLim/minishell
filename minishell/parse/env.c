#include "../minishell.h"

int	replace_and_check(char **str, t_vars *vars)
{
	char	*mem;

	mem = *str;
	*str = replace_env_vars(*str, vars->env);	// 환경변수 치환
	use_free(mem);
	if (is_valid_quotes(*str) == 0)				// 따옴표 검사
	{
		use_free(*str);
		error_msg("Invalid quotes");
		return (0);
	}
	return (1);
}

char	*replace_env_vars(char *content, t_env *env)
{
	char	*result;
	int		i;
	int		flag;

	result = ft_strdup("");
	i = 0;
	flag = 0;
	while (content[i] != '\0')
	{
		if (content[i] == '\'')
			flag = !flag;
		if (is_envvar(content, i, flag))
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
