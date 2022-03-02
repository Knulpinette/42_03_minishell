#include "minishell.h"

static int		nb_of_letters_if_quotes(const char *s, int i, int letters, t_token *token, char c)
{
	if (s[i + letters] == SGL_QUOTE && ft_strchr(s, SGL_QUOTE))
	{
		letters = letters + quote_len(s, c, SGL_QUOTE, (i + letters));
		token->quote = SGL_QUOTE;
	}
	else if (s[i + letters] == DBL_QUOTE && ft_strchr(s, DBL_QUOTE))
	{
		letters = letters + quote_len(s, c, DBL_QUOTE, (i + letters));
		token->quote = DBL_QUOTE;
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
		while (s[i + letters] && s[i + letters] != c)
		{
			letters = nb_of_letters_if_quotes(s, i, letters, &tokens[word], c);
			letters++;
		}
		tokens[word].text = calloc_or_exit(sizeof(char), letters + 1);
		j = 0;
		while (j < letters)
			tokens[word].text[j++] = s[i++];
		tokens[word++].text[j] = 0;
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
