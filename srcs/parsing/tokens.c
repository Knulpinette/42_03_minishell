#include "minishell.h"

static int		nb_of_letters_if_quotes(const char *s, int i, int letters, t_token *token, char c)
{
	char quote;

	quote = 0;
	if (s[i + letters] == SGL_QUOTE || s[i+letters] == DBL_QUOTE)
	{
		quote = s[i + letters];
		if (ft_strrchr((s + i + letters), quote) != (s + i + letters))
		{
			letters = letters + quote_len(s, c, quote, (i + letters));
			DEBUG(printf("after quote len%c\n", s[i + letters]);)
			token->quote = quote;
		}
	}
	return (letters);
}

static t_token	*fill_tokens(const char *s, char c, int words, t_token *tokens)
{
	int		i;
	int		j;
	int		word;
	int		letters;

	i = 0;
	word = 0;
	while (word < words && s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		letters = 0;
		DEBUG(printf("______\ncounting nb_letters in token\n");)
		while (s[i + letters] && s[i + letters] != c)
		{
			letters = nb_of_letters_if_quotes(s, i, letters, &tokens[word], c);
			if (s[i + letters] != c)
				letters++;
		}
		DEBUG(printf("%i\n", letters);)
		tokens[word].text = calloc_or_exit(sizeof(char), letters + 1);
		j = 0;
		DEBUG(printf("\n_____\nsaving token\n");)
		while (j < letters)
		{
			tokens[word].text[j++] = s[i++];
			DEBUG(printf("%c / ", tokens[word].text[j - 1]);)
		}
		tokens[word++].text[j] = 0;
		DEBUG(printf("\ndone saving token\n_____\n");)
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
