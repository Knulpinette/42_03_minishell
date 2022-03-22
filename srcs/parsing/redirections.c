#include "minishell.h"

t_redir	*get_redirs(char *instructions, t_redir *redirs, int nb_redirs)
{
	int i;

	i = 0;
	(void)nb_redirs;
	(void)instructions;
	(void)i;
	return (redirs);
}



/*
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
*/