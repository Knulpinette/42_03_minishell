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

char	*rewrite_instruction_with_env_var(char *instruction)
{
	char *rewrite;

	(void)rewrite;
	//free(instructions)
	return (instruction); 
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


// PROBABLY CAN DELETE THOSE TWO FUNCTIONS AND REWRITE THEM!

/*void	setup_all_variables_with_dbl_quotes_exception(
			t_token *token, char **env_var, int *len_token)
{
	char	*starting_point;
	int		env_var_len;

	*env_var = NULL;
	*len_token = ft_strlen(token->text) - 2;
	if (ft_strchr(token->text, '$') && token->quote == DBL_QUOTE)
	{
		starting_point = ft_strchr(token->text, '$') + 1;
		env_var_len = get_env_var_len(token->text, DBL_QUOTE);
		*env_var = get_env_var(starting_point, env_var_len, DBL_QUOTE);
		*len_token = (*len_token) - env_var_len + ft_strlen(*env_var); 
	}
}

// handle problem of removing extra quote if "yo""this""hello 

void	remove_quotes(t_token *token)
{
	char	*temp;
	char	*env_var;
	int		len_token;
	int		i;
	int		j;

	setup_all_variables_with_dbl_quotes_exception(token, &env_var, &len_token);
	temp = calloc_or_exit(sizeof(char), len_token + 1);
	i = 0;
	j = 0;
	while (token->text[i])
	{
		if (token->text[i] == '$' && token->quote == DBL_QUOTE)
		{
			i = i + get_env_var_len(token->text, DBL_QUOTE);
			j = j + ft_strlcpy(&temp[j], env_var, ft_strlen(env_var) + 1);
		}
		else if (token->text[i] != token->quote)
			temp[j++] = token->text[i];
		i++;
	}
	if (env_var)
		free(env_var);
	free(token->text);
	token->text = strdup(temp);
	free(temp); 
}*/
