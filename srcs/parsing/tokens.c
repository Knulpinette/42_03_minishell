#include "minishell.h"

/*

ONGOING 

// go with t_tokens or t_list ? 

Parsing tokens
{
	while (instructions)
	{
		if SNG_QUOTE || DBLE_QUOTE
			check_for_a_second_one();
				if (true)
					get_text_in_between_as_string();
	}
}
*/

static int	nb_words(const char *s, char c)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (s[i])
	{
		if (s[i] == SGL_QUOTE && ft_strchr(s, SGL_QUOTE))
		{
			i++;
			while (s[i] && s[i] != SGL_QUOTE)
				i++;
			nb++;
		}
		else if (s[i] == DBL_QUOTE && ft_strchr(s, DBL_QUOTE))
		{
			i++;
			while (s[i] && s[i] != DBL_QUOTE)
				i++;
			nb++;
		}
		else if (s[i] != c && (s[i + 1] == 0 || s[i + 1] == c))
			nb++;
		i++;
	}
	return (nb);
}

static char	**fill_tokens(const char *s, char c, int words, char **tokens)
{
	int		i;
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
			letters++;
		tokens[word] = (char *)malloc(sizeof(char) * (letters + 1));
		if (!tokens[word])
			return (NULL);
		letters = 0;
		while (s[i] && s[i] != c)
			tokens[word][letters++] = s[i++];
		tokens[word++][letters] = 0;
	}
	tokens[word] = 0;
	return (tokens);
}

char	**tokenise(const char *s, char c)
{
	int		words;
	char	**tokens;

	if (!s)
		return (NULL);
	words = nb_words(s, c);
	tokens = (char **)malloc(sizeof(char *) * (words + 1));
	if (!tokens)
		return (NULL);
	fill_tokens(s, c, words, tokens);
	return (tokens);
}
