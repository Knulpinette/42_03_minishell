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

static int	quote_word_count(const char *s, char c, char quote, int i)
{
	while (s[i] && s[i] != quote && s[i + 1])
		i++;
	if (s[i] != c && (s[i + 1] == 0 || s[i + 1] == c))
	{
		if (s[i] == quote && s[i + 1])
			i++;
		return (1);
	}
	return (0);
}

static int	quote_len(const char *s, char c, char quote, int i)
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

int		get_nb_tokens(const char *s, char c)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (s[i])
	{
		if (s[i] == SGL_QUOTE && ft_strchr(s, SGL_QUOTE))
		{
			nb = nb + quote_word_count(s, c, SGL_QUOTE, i + 1);
			i = i + quote_len(s, c, SGL_QUOTE, i);
		}
		else if (s[i] == DBL_QUOTE && ft_strchr(s, DBL_QUOTE))
		{
			nb = nb + quote_word_count(s, c, DBL_QUOTE, i + 1);
			i = i + quote_len(s, c, DBL_QUOTE, i);
		}
		else if (s[i] != c && (s[i + 1] == 0 || s[i + 1] == c))
				nb++;
		i++;
	}
	DEBUG(printf("nb_tokens : %i\n", nb);)
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
		// here check to get the righ number of letters for the quote
			letters++;
		tokens[word] = (char *)malloc(sizeof(char) * (letters + 1));
		if (!tokens[word])
			return (NULL);
		letters = 0;
		while (s[i] && s[i] != c)
			tokens[word][letters++] = s[i++];
		tokens[word++][letters] = 0;
	}
	return (tokens);
}

char	**tokenise(const char *s, char c, int words)
{
	char	**tokens;

	if (!s)
		return (NULL);
	tokens = (char **)malloc(sizeof(char *) * words);
	if (!tokens)
		return (NULL);
	fill_tokens(s, c, words, tokens);
	DEBUG(print_split(tokens);)
	return (tokens);
}
