#include "minishell.h"

char	check_quote(char letter, char quote)
{
	if ((letter == DBL_QUOTE || letter == SGL_QUOTE) &&
		(!quote || (quote && letter == quote)))
	{
		if (quote)
			quote = 0;
		else
			quote = letter;
	}
	return (quote);
}

char	check_valid_quote(char *text, char quote)
{
	if (ft_strchr((text + 1), quote))
		return (quote);
	return (0);
}

bool	there_is_quote(char *text, char quote)
{
	int		i;

	i = 0;
	while (text[i])
	{
		if (text[i] == quote &&	ft_strchr((text + i + 1), quote))
				return (true);
		i++;
	}
	return (false);
}

int		get_nb_quotes(char *text)
{
	int		count;
	char	quote;

	quote = 0;
	count = 0;
	while (*text)
	{
		if ((*text == DBL_QUOTE || *text == SGL_QUOTE) &&
		(!quote || (quote && *text == quote)))
		{
			if (quote)
			{
				quote = 0;
				count++;
			}
			else
				quote = *text;
		}
		text++;
	}
	return (count * 2);
}

char	*remove_quotes(char *text)
{
	char	*temp;
	char	quote;
	int		len_token;
	int		i;
	int		j;

	len_token = ft_strlen(text) - get_nb_quotes(text);
	temp = calloc_or_exit(sizeof(char), len_token + 1);
	i = 0;
	j = 0;
	quote = 0;
	while (text[i])
	{
		if (text[i] == DBL_QUOTE || text[i] == SGL_QUOTE)
			quote = check_valid_quote((text + i), text[i]);
		if (quote && text[i++])
		{
			while (text[i] && text[i] != quote)
				temp[j++] = text[i++];
			quote = 0;
			i++;
		}
		else
			temp[j++] = text[i++];
	}
	temp[j] = 0;
	free(text);
	return (temp);
}
