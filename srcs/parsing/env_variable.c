#include "minishell.h"

int		get_env_var_len(char *text, char delim)
{
	int	i;
	int	env_var_len;

	i = 0;
	env_var_len = 0;
	while (text[i] != '$')
		i++;
	i++;
	while (text[i + env_var_len] != delim)
		env_var_len++;
	return (env_var_len);
}

char	*get_env_var(char *text, int env_var_len, char delim)
{
	char	*env_var;
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	env_var = calloc_or_exit(sizeof(char), env_var_len + 1);
	while (text[i] != delim)
	{
		env_var[j++] = text[i++];
	}
	env_var[j] = 0;
	if (getenv(env_var))
		result = strdup(getenv(env_var));
	else
		result = strdup("");
	free(env_var);
	DEBUG(printf("env_var_real_path = %s\n", result);)
	return (result);
}
