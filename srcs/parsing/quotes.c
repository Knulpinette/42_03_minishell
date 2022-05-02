#include "minishell.h"

/*
** 🦕🌴
** check_quote
**
** This is a very little function, but wht an important one!!
** The whole parsing relies on it and it is saving many, many,
**	many lines of codes and headaches.
**
** This function acts as a boolean in the form of a char. It will
**	either put 'quote' to SGL_QUOTE or DBL_QUOTE or NULL depending
**	on the scenario. 
**
**	OPEN QUOTE: If the given character is a quote, and quote is 0,
**	we change quote to the given character.
**	CLOSED QUOTE: If the given character is a quote, and quote is
**	the same quote as the given character, we change quote back to 0.
**
** 🌴🥥
*/

char	check_quote(char letter, char quote)
{
	if ((letter == DBL_QUOTE || letter == SGL_QUOTE)
		&& (!quote || (quote && letter == quote)))
	{
		if (quote)
			quote = 0;
		else
			quote = letter;
	}
	return (quote);
}

/*
** check_valid_quote
**
** Here we are checking that the quote we entered is a closed
**	quote and not an open one.
**
*/

char	check_valid_quote(char *text, char quote)
{
	if (ft_strchr((text + 1), quote))
		return (quote);
	return (0);
}

/*
** there_is_quote
**
** We check there is a closed quote in a given string.
**
*/

bool	there_is_quote(char *text, char quote)
{
	int		i;

	i = 0;
	while (text[i])
	{
		if (text[i] == quote && ft_strchr((text + i + 1), quote))
			return (true);
		i++;
	}
	return (false);
}

/*
** get_nb_quotes
**
**	Here we check how many closed quotes there are.
**	The logic is that every time a quote closes, we increment
**	count. Effectively, we're counting how many times there
**	are closed quotes, which is why we multiply that count by
**	two at the end since every closed quote is made with two quotes.
**
*/

int	get_nb_quotes(char *text)
{
	int		count;
	char	quote;

	quote = 0;
	count = 0;
	while (*text)
	{
		if ((*text == DBL_QUOTE || *text == SGL_QUOTE)
			&& (!quote || (quote && *text == quote)))
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

/*
**	remove_quotes
**
** This function removes all closed quotes from a given string
**	and returns the new cleaned up string as a result.
**	It frees the given string before exiting since it is meant
**	to be used as a rewriting function.
**
*/

// FUCTION HAS MORE THAN 25 LINES !!

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
