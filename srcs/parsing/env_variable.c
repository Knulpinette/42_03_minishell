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

/*char  *replace_with_env_var(char *instruction)
{
    char    *new_instruction;
    int     len_new_instruction;
    int     temp_len;
    int     quotes_count;
 
    first get len of everything => go through everything once
    then do it again, but this time with the right infos
    quotes_count = 0;
    env_var_len = get_env_var_len;
    env_var = get_env_var();
 
    // change env_var in the first stage => rewrite the instruction line
    // have a counter : quote_count = 0; if ", quote_count = 1; if " again, quote_count = 2; reset
    // => if env_var && quote_count = 2 => write env_var. If not, free it and ignore.
    // also have a count to know how long string is going to be.
 
    allocate (new_instruction);
    free(instruction);
    return (new_instruction);
}*/
// then get rid of " and ' exeception for env_var in rest of code.
