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

char	*rewrite_instruction_with_env_var(char *instruction)
{
	char	*temp;
	char	quote;
	char	**env_var;
	int		len_instruction;
	int		count;
	int		i;
	int		j;

	quote = 0;
	env_var = get_env_var_split(instruction);
	len_instruction = get_len_instruction(instruction, env_var);
	temp = calloc_or_exit(sizeof(char), len_instruction + 1);
	DEBUG(printf("len_instruction = %i\n", len_instruction);)
	count = 0;
	i = 0;
	j = 0;
	while (instruction[i])
	{
		quote = check_quote(*instruction, quote);
		DEBUG(printf("début boucle : i = %i >> j = %i\n", i, j);)
		if (*instruction == '$' && quote != SGL_QUOTE && env_var)
		{
			int save;
			
			save = ft_strlcpy(temp + j, env_var[count], ft_strlen(env_var[count]) + 1);
			DEBUG(printf("len_of_copied_env_var_path = %i\n", save);)
			j = j + save;
			//j += ft_strlcpy(temp + j, env_var[count], ft_strlen(env_var[count]) + 1);
			DEBUG(printf("len_of_$_env_var = %i & env_var_$ = %s\n", get_env_var_len(instruction + i, SPACE, '$'), instruction + i);)
			i = i + get_env_var_len(instruction + i, SPACE, '$');
			DEBUG(printf("i after env_var = %i\n", i);)
			count++;
		}
		else
		{
			temp[j++] = instruction[i++];
			DEBUG(printf("temp[j] = %c || instruction[i] = %c\n", temp[j - 1], instruction[i - 1]);)
		}
	}
	DEBUG(printf("temp = %s\n", temp);)
	free_split(env_var);
	return (temp); 
}
