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
