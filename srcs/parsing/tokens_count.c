#include "minishell.h"

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
	//DEBUG(printf("nb_tokens : %i\n", nb);)
	return (nb);
}
