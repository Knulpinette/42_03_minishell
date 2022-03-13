#include "minishell.h"

void	get_tokens_types(t_token *tokens, int nb_tokens)
{
	int	i;

	i = 0;
	while (i < nb_tokens)
	{
		if (tokens[i].quote)
			remove_quotes(&tokens[i]);
		//check_for_redir => get all info and go along the right amount of tokens
		//then => next token == cmd
		if (i == 0)
			tokens[i].type = CMD;
		else if (tokens[i].text[0] == '-' && tokens[i].text[1])
			tokens[i].type = FLAG;
		else if (ft_strchr(tokens[i].text, '$') && tokens[i].quote != SGL_QUOTE)
			tokens[i].type = ENV_VAR;
		else if (ft_strchr(tokens[i].text, '<'))
		{
			if (*(ft_strchr(tokens[i].text, '<') + 1) == '<')
				tokens[i].type = OP_DELIMITER;
			else
				tokens[i].type = OP_REDIR_IN;
		}
		else if (ft_strchr(tokens[i].text, '>'))
		{
			if (*(ft_strchr(tokens[i].text, '>') + 1) == '>')
				tokens[i].type = OP_APPEND;
			else
				tokens[i].type = OP_REDIR_OUT;
		}
		else
			tokens[i].type = WORD;
		i++;
	}
	return ;
}	
