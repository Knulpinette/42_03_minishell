#include "minishell.h"

static int	get_len_instruction(char *instruction, char **env_var)
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
			while (instruction[i] && is_not_exception(instruction[i]))
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

static char	*write_env_var_to_temp(char *instruction, char **env_var, int	len_instruction)
{
	char	*temp;
	char	quote;
	int		count;
	int		i;
	int		j;

	temp = calloc_or_exit(sizeof(char), len_instruction + 1);
	quote = 0;
	count = 0;
	i = 0;
	j = 0;
	while (instruction[i])
	{
		quote = check_quote(*instruction, quote);
		if (instruction[i] == '$' && quote != SGL_QUOTE && env_var[count])
		{
			//DEBUG(printf("before\n> instruction[i] = %c\n>> i = %i\n>> j = %i\n", instruction[i], i, j);)
			j += ft_strlcpy(temp + j, env_var[count], ft_strlen(env_var[count]) + 1);
			i = i + get_env_var_len(instruction + i);
			count++;
			//DEBUG(printf("after \n> instruction[i] = %c\n>> i = %i\n>>j = %i\n", instruction[i], i, j);)
		}
		else
			temp[j++] = instruction[i++];
	}
	temp[j] = 0;
	return (temp);
}

char		*rewrite_instruction_with_env_var(char *instruction)
{
	char	*temp;
	char	**env_var;
	int		len_instruction;

	env_var = get_env_var_split(instruction);
	len_instruction = get_len_instruction(instruction, env_var);
	//DEBUG(printf(">>> len_instruction = %i\n", len_instruction);)
	temp = write_env_var_to_temp(instruction, env_var, len_instruction);
	free_split(env_var);
	return (temp); 
}

static char	*erase_redirs(char *instruction, int len)
{
	char	*temp;
	char	quote;
	int		i;
	int		j;

	temp = calloc_or_exit(sizeof(char), len + 1);
	quote = 0;
	i = 0;
	j = 0;
	while (instruction[i])
	{
		quote = check_quote(instruction[i], quote);
		if ((instruction[i] == '<' || instruction[i] == '>') && !quote)
			i += pass_redir(instruction + i);
		else
			temp[j++] = instruction[i++];
	}
	return (temp);
}

char		*rewrite_instruction_without_redirs(char *instruction)
{
	char	*temp;
	char	quote;
	int		len;
	int		i;

	quote = 0;
	len = 0;
	i = 0;
	while (instruction[i + len])
	{
		quote = check_quote(instruction[i + len], quote);
		if ((instruction[i + len] == '<' || instruction[i + len] == '>') && !quote)
			i += pass_redir(instruction + i + len);
		else
			len++;
	}
	temp = erase_redirs(instruction, len);
	return (temp);
}
