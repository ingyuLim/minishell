#include "../minishell.h"

int	is_include_dollar(char *str)
{
	int	i;
	int	flag;	// 0 : 따옴표 밖, 1 : 따옴표 안

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

// "$USER $USER" => "seunan seunan"
char	*replace_env_vars(char *content, t_env *env)
{
	char	*result;
	char	*key;
	char	*tmp;
	int		i;
	int		j;
	int		flag;

	result = ft_strdup("");
	i = 0;
	flag = 0;
	while (content[i] != '\0')
	{
		if (content[i] == '\'')
			flag = !flag;
		if (content[i] == '$' && content[i + 1] != '\0' && content[i + 1] != ' '&& !ft_isquote(content[i + 1]) && content[i + 1] != '$' && !flag)
		{
			j = i + 1;
			while (content[j] != '\0' && content[j] != ' ' && !ft_isquote(content[j]) && content[j] != '$')
				j++;
			key = ft_substr(content, i + 1, j - i - 1);
			tmp = result;
			result = ft_strjoin(result, find_env(key, env));
			use_free(tmp);
			use_free(key);
			i = j;
		}
		else
		{
			result = ft_strjoin_char(result, content[i]);
			++i;
		}
	}
	use_free(content);
	return (result);
}
