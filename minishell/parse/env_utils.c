#include "../minishell.h"

int	is_envvar(char *content, int i)
{
	if (content[i] == '$' && content[i + 1] != '\0' && !ft_iswhitespace(content[i + 1])&& !ft_isquote(content[i + 1]) && content[i + 1] != '$')
		return (1);
	return (0);
}

int	is_state(char *content, int i)
{
	if (content[i + 1] == '?' && (content[i + 2] == '\0' || !ft_iswhitespace(content[i + 2])|| ft_isquote(content[i + 2]) || content[i + 2] == '$'))
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
