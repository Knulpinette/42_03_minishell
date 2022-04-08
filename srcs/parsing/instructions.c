#include "minishell.h"

/* Note: any input that has an open quote will be recorded
** as one command instead of two. 
** Is that ok?
** for example:
** > ls -l | echo hello
**		ls -l
**		echo hello
** > ls -l " | echo hello
**		ls -l " | echo hello
*/

static	int		nb_words(const char *s, char c)
{
	int		i;
	int		nb;
	char	quote;

	i = 0;
	nb = 0;
	quote = 0;
	while (s[i])
	{
		quote = check_quote(s[i], quote);
		if (s[i] != c && (s[i + 1] == 0 || (s[i + 1] == c && !quote)))
			nb++;
		i++;
	}
	return (nb);
}

static	char	**fill_instructions(const char *s, char c, int words, char **split)
{
	int		i;
	int		j;
	int		word;
	int		letters;
	char	quote;

	i = 0;
	word = 0;
	quote = 0;
	while (word < words)
	{
		while (s[i] && s[i] == c)
			i++;
		letters = 0;
		while (s[i + letters] && ((s[i + letters] != c && !quote) || quote))
		{
			quote = check_quote(s[i + letters], quote);
			letters++;
		}
		split[word] = (char *)malloc(sizeof(char) * (letters + 1));
		if (!split[word])
			return (NULL);
		j = 0;
		while (s[i] && j < letters)
			split[word][j++] = s[i++];
		split[word++][j] = 0;
	}
	split[word] = 0;
	return (split);
}

char	**get_instructions(const char *s, char c)
{
	int		words;
	char	**split;

	if (!s)
		return (NULL);
	words = nb_words(s, c);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	fill_instructions(s, c, words, split);
	return (split);
}

static	char *write_env_var_to_temp(char *instruction, char **env_var, int	len_instruction)
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
		{
			temp[j++] = instruction[i++];
			//DEBUG(printf("else \n> instruction[i] = %c\n>> i = %i\n>>j = %i\n", instruction[i - 1], i - 1, j - 1);)
		}
	}
	temp[j] = 0;
	return (temp);
}

char	*rewrite_instruction_with_env_var(char *instruction)
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
