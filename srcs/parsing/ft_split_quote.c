#include "minishell.h"

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

static	char	**fill_split(const char *s, char c, int words, char **split)
{
	int		i;
	int		word;
	int		letters;
	int		saved;
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
		saved = i + letters;
		letters = 0;
		while (s[i] && i < saved)
			split[word][letters++] = s[i++];
		split[word++][letters] = 0;
	}
	split[word] = 0;
	return (split);
}

char	**ft_split_quote(const char *s, char c)
{
	int		words;
	char	**split;

	if (!s)
		return (NULL);
	words = nb_words(s, c);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	fill_split(s, c, words, split);
	return (split);
}
