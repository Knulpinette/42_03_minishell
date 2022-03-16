#include "minishell.h"

static int	quote_word_count(const char *s, char c, char quote, int i)
{
	DEBUG(printf("_____\nentering word count\n");)
	while (s[i] && s[i] != quote && s[i + 1])
		i++;
	if (s[i] != c)
	{
		if (s[i])
			i++;
		if (s[i] == 0 || s[i] == c)
			return (1);
	}
	return (0);
}

int		quote_len(const char *s, char c, char quote, int i)
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
	int			i;
	int			nb;
	char		quote;

	i = 0;
	nb = 0;
	quote = 0;
	while (s[i])
	{
		if (s[i] == SGL_QUOTE || s[i] == DBL_QUOTE)
		{
			quote = s[i];
			if (ft_strrchr((s + i), quote) != (s + i))
			{
				nb = nb + quote_word_count(s, c, quote, i + 1);
				i = i + quote_len(s, c, quote, i);
			}
		}
		else if (s[i] != c && (s[i + 1] == 0 || s[i + 1] == c))
				nb++;
		i++;
	}
	DEBUG(printf("\n>>> nb_tokens : %i <<<\n", nb);)
	return (nb);
}
