#include "minishell.h"

void	get_tokens_types(t_token *tokens, int nb_tokens)
{
	int	i;

	i = 0;
	while (i < nb_tokens)
	{
		if (there_is_quote(tokens[i].text, DBL_QUOTE) ||
				there_is_quote(tokens[i].text, SGL_QUOTE))
			tokens[i].text = remove_quotes(tokens[i].text);
		if (i == 0)
			tokens[i].type = CMD;
		else if (tokens[i].text[0] == '-' && tokens[i].text[1])
			tokens[i].type = FLAG;
		else
			tokens[i].type = WORD;
		i++;
	}
	return ;
}	
