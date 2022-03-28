#include "minishell.h"

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
		quote = check_quote(s[i], quote);
		if (s[i] != c && (s[i + 1] == 0 || (s[i + 1] == c && !quote)))
				nb++;
		i++;
	}
	DEBUG(printf("\nnb_tokens : %i\n", nb);)
	return (nb);
}
