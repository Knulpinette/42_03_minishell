#include "minishell.h"

int				quote_len(const char *s, char c, char quote, int i)
{
	int i_start;

	i_start = i;
	i++;
	while (s[i] && s[i] != quote && s[i + 1])
		i++;
	if (s[i] != c && (s[i + 1] == 0 || s[i + 1] == c))
	{
		if (s[i] == quote && s[i + 1])
			i++;
	}
	return (i - i_start);
}

static int		handle_quotes(const char *s, int i, int letters, t_token *tokens, char c)
{
	if (s[i + letters] == SGL_QUOTE && ft_strchr(s, SGL_QUOTE))
		{
			letters = letters + quote_len(s, c, SGL_QUOTE, (i + letters));
			tokens->quote = SINGLE;
		}
		else if (s[i + letters] == DBL_QUOTE && ft_strchr(s, DBL_QUOTE))
		{
			letters = letters + quote_len(s, c, DBL_QUOTE, (i + letters));
			tokens->quote = DOUBLE;
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
	while (word < words)
	{
		while (s[i] && s[i] == c)
			i++;
		letters = 0;
		while (s[i + letters] && s[i + letters] != c)
			letters = handle_quotes(s, i, letters, &tokens[word], c) + 1; // here we do letters++ every time + length of quote if there's one to handle.
		tokens[word].text = calloc_or_exit(sizeof(char), letters + 1);
		j = 0;
		while (j < letters)
			tokens[word].text[j++] = s[i++];
		tokens[word++].text[j] = 0; // not necessary (well word++ is) but keep for redonduncy ?
	}
	return (tokens);
}

t_token			*tokenise(const char *s, char c, int words)
{
	t_token	*tokens;

	if (!s)
		return (NULL);
	tokens = calloc_or_exit(sizeof(t_token), words);
	fill_tokens(s, c, words, tokens);
	DEBUG(print_tokens(tokens, words);)
	return (tokens);
}
