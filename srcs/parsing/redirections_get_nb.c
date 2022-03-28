#include "minishell.h"

int	get_nb_redirs(char *instructions)
{
	int		count_redirs;
	int		i;
	char	quote;
	char	redir;

	count_redirs = 0;
	i = 0;
	quote = 0;
	redir = 0;
	while (instructions[i])
	{
		quote = check_quote(instructions[i], quote);
		if ((instructions[i] == '<' || instructions[i] == '>') && !quote)
		{
			redir = instructions[i];
			i++;
			if (instructions[i] && instructions[i] == redir)
				i++;
			count_redirs++;
		}
		else
			i++;
	}
	DEBUG(printf("count of redirs = %i\n", count_redirs);)
	return (count_redirs);
}

		/*	else if (ft_strchr(tokens[i].text, '<'))
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
				tokens[i].type = OP_REDIR_OUT; */