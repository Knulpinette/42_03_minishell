#include "minishell.h"

/*
** 🦕🌴
**
** get_env_var
** 
** Those functions build up a null terminated array**
**	of environement variables.
**	⚠️ If the $ENV_VAR is in between single quotes, it is ignored.
**	1. We get the number of environement variables (while taking the
**		quote rule into account.)
**	2. We get the length of the '$ENV_VAR' written in the instruction
**		line. (Will be used to save that text temporarily when getting
**		the path).
**	3. Then we extract the real path of the env_variable and return the
**		result as an allocated string.
**		If the env_var doesn't exist, we return an empty string.
**
** 🌴🥥
*/

int		get_nb_env_var(char	*text)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (text[i])
	{
		quote = check_quote(text[i], quote);
		if (text[i] == '$' && quote != SGL_QUOTE)
			count++;
		i++;
	}
	return (count);
}

int		get_env_var_len(char *text)
{
	int	env_var_len;

	env_var_len = 1; // to handle the '$'
	while (text[env_var_len] && is_not_exception(text[env_var_len], ENV_VAR))
		env_var_len++;
	return (env_var_len);
}

char	*get_env_var(char *text, int env_var_len)
{
	char	*env_var;
	char	*result;
	int		i;
	int		j;

	i = 1; // to handle the '$'
	j = 0;
	env_var = calloc_or_exit(sizeof(char), env_var_len + 1);
	while (text[i] && is_not_exception(text[i], ENV_VAR))
		env_var[j++] = text[i++];
	if (getenv(env_var))
		result = strdup(getenv(env_var));
	else
		result = strdup("");
	free(env_var);
	DEBUG(printf("env_var_real_path = %s\n", result);)
	return (result);
}

char	**get_env_var_split(char *instruction)
{
	int		nb_env_var;
	int		env_var_len;
	int		count;
	char	quote;
	char	**env_var;

	count = 0;
	quote = 0;
	nb_env_var = get_nb_env_var(instruction);
	env_var = calloc_or_exit(sizeof(char *), nb_env_var + 1);
	while (count < nb_env_var && *instruction)
	{
		quote = check_quote(*instruction, quote);
		if (*instruction == '$' && quote != SGL_QUOTE)
		{
			env_var_len = get_env_var_len(instruction);
			env_var[count] = get_env_var(instruction, env_var_len);
			count++;
		}
		instruction++;
	}
	env_var[count] = 0;
	return (env_var);
}
