#include "minishell.h"

static t_token	*fill_tokens(const char *s, char c, int words, t_token *tokens)
{
	int		i;
	int		j;
	int		word;
	int		letters;
	char	quote;

	i = 0;
	word = 0;
	quote = 0;
	while (word < words && s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		letters = 0;
		//DEBUG(printf("______\ncounting nb_letters in token\n");)
		while (s[i + letters] && ((s[i + letters] != c && !quote) || quote))
		{
			quote = check_quote(s[i + letters], quote);
			letters++;
		}
		//DEBUG(printf("%i\n", letters);)
		tokens[word].text = calloc_or_exit(sizeof(char), letters + 1);
		j = 0;
		//DEBUG(printf("\n_____\nsaving token\n");)
		while (s[i] && j < letters)
		{
			tokens[word].text[j++] = s[i++];
			//DEBUG(printf("%c / ", tokens[word].text[j - 1]);)
		}
		tokens[word++].text[j] = 0;
		//DEBUG(printf("\ndone saving token\n_____\n");)
	}
	return (tokens);
}

t_token			*get_tokens(const char *s, char c, int words)
{
	t_token	*tokens;

	if (!s)
		return (NULL);
	tokens = calloc_or_exit(sizeof(t_token), words);
	fill_tokens(s, c, words, tokens);
	return (tokens);
}
