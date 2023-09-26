#include "../minishell.h"

int	is_include_dollar(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i] != '\0')
	{
		if (flag && str[i] == '\'')
			flag = 0;
		else if (!flag && str[i] == '\'')
			flag = 1;
		else if (!flag && str[i] == '$' && str[i + 1] != '\0' && str[i + 1] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	is_envvar(char *content, int i, int flag)
{
	if (content[i] == '$' && content[i + 1] != '\0' && content[i + 1] != ' '&& !ft_isquote(content[i + 1]) && content[i + 1] != '$' && !flag)
		return (1);
	return (0);
}

int	is_state(char *content, int i)
{
	if (content[i + 1] == '?' && (content[i + 2] == '\0' || content[i + 2] == ' '|| ft_isquote(content[i + 2]) || content[i + 2] == '$'))
		return (1);
	return (0);
}

char	*find_env(char *key, t_env *env)
{
	while (env != NULL)
	{
		if (ft_strncmp(key, env->key, ft_strlen(key) + 1) == 0)
			return (env->value);
		env = env->next;
	}
	return ("");
}

char	*ft_strjoin_char(char *s1, char c)
{
	char	*result;
	int		i;

	result = ft_calloc(ft_strlen(s1) + 2, sizeof(char));
	i = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		++i;
	}
	result[i] = c;
	use_free(s1);
	return (result);
}
