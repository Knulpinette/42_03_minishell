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
			//DEBUG(printf("entering quote copy\nquote = %c && text[i] = %c\n", quote, text[i]);)
			while (text[i] && text[i] != quote)
			{
				temp[j++] = text[i++];
				//DEBUG(printf("temp[j] = %c && text[i] = %c\n", temp[j - 1], text [i - 1]);)
			}
			quote = 0;
			//DEBUG(printf("exiting\nquote = %c && text[i] = %c\n", quote, text[i]);)
			i++;
			//DEBUG(printf("text[i++] = %c\n", text[i]);)
		}
		else
			temp[j++] = text[i++];
	}
	temp[j] = 0;
	free(text);
	return (temp);
}
