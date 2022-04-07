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
	int	env_var_len;

	env_var_len = 1; // to handle the '$'
	while (text[env_var_len] && (text[env_var_len] != delim1 && text[env_var_len] != delim2))
		env_var_len++;
	return (env_var_len);
}

char	*get_env_var(char *text, int env_var_len, char delim1, char delim2)
{
	char	*env_var;
	char	*result;
	int		i;
	int		j;

	i = 1; // to handle the '$'
	j = 0;
	env_var = calloc_or_exit(sizeof(char), env_var_len + 1);
	while (text[i] && (text[i] != delim1 && text[i] != delim2))
		env_var[j++] = text[i++];
	if (getenv(env_var))
		result = strdup(getenv(env_var));
	else
		result = strdup("");
	free(env_var);
	DEBUG(printf("env_var_real_path = %s\n", result);)
	return (result);
}

int		get_len_instruction(char *instruction, char **env_var)
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
			while (instruction[i] && (instruction[i] != SPACE && instruction[i] != '$'))
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
	int		len_instruction;
	int		count;
	int		i;
	int		j;

	temp = NULL;
	quote = 0;
	env_var = get_env_var_split(instruction);
	len_instruction = get_len_instruction(instruction, env_var);
	temp = calloc_or_exit(sizeof(char), len_instruction + 1);
	count = 0;
	i = 0;
	j = 0;
	while (instruction[i])
	{
		quote = check_quote(*instruction, quote);
		if (*instruction == '$' && quote != SGL_QUOTE)
		{
			j += ft_strlcpy(temp + j, env_var[count], ft_strlen(env_var[count]) + 1);
			i += get_env_var_len(instruction + i, SPACE, '$');
			count++;
		}
		else
			temp[j++] = instruction[i++];
	}
	free_split(env_var);
	return (temp); 
}
