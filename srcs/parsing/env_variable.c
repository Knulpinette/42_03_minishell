#include "minishell.h"

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

int		get_env_var_len(char *text, char delim1, char delim2)
{
	int	i;
	int	env_var_len;

	i = 0;
	env_var_len = 0;
	i++;
	while (text[i + env_var_len] != delim1 || text[i + env_var_len] != delim2)
		env_var_len++;
	return (env_var_len);
}

char	*get_env_var(char *text, int env_var_len, char delim1, char delim2)
{
	char	*env_var;
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	env_var = calloc_or_exit(sizeof(char), env_var_len + 1);
	while (text[i] != delim1 ||text[i] != delim2)
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

int		get_len_token(char *instruction, char **env_var)
{
	int		len;
	int		i;
	char	quote;
	int		count;

	len = 0;
	i = 0;
	quote = 0;
	count = 0;
	while (instruction[i])
	{
		quote = check_quote(instruction[i], quote);
		if (instruction[i] == '$' && quote != SGL_QUOTE)
		{
			i++;
			len = len + ft_strlen(env_var[count++]);
			while (instruction[i] != SPACE || instruction[i] != '$')
				i++;
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
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
			env_var_len = get_env_var_len(instruction, SPACE, '$');
			env_var[count] = get_env_var(instruction, env_var_len, SPACE, '$');
			count++;
		}
		instruction++;
	}
	env_var[count] = 0;
	return (env_var);
}

char	*rewrite_instruction_with_env_var(char *instruction)
{
	char	*temp;
	char	quote;
	char	**env_var;
	int		len_token;
	int		count;

	temp = NULL;
	quote = 0;
	env_var = get_env_var_split(instruction);
	len_token = get_len_token(instruction, env_var);
	temp = calloc_or_exit(sizeof(char), len_token + 1);
	count = 0;
	while (*instruction)
	{
		quote = check_quote(*instruction, quote);
		if (*temp == '$')
		{
			if (quote != SGL_QUOTE)
			{
				temp = temp + ft_strlcpy(temp, env_var[count], ft_strlen(env_var[count]) + 1);
				count++;
			}
		}
		else
			*temp = *instruction;
		temp++;
		instruction++;
	}
	*instruction = 0;
	free_split(env_var);
	free(instruction);
	return (temp); 
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
