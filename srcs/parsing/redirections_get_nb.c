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
		DEBUG(printf("while (instructions[i])\ni = %i\ninstruction[i] = %c\nquote = %c\n", i, instructions[i], quote);)
		if ((instructions[i] == '<' || instructions[i] == '>') && !quote)
		{
			DEBUG(printf("if ((instructions[i] == '<' || instructions[i] == '>') && !quote)\ni = %i\ninstruction[i] = %c\n", i, instructions[i]);)
			redir = instructions[i];
			i++;
			DEBUG(printf("i++;\ni = %i\ninstruction[i] = %c\n", i, instructions[i]);)
			if (instructions[i] && instructions[i] == redir)
			{
				i++;
				DEBUG(printf("if (instructions[i] && instructions[i] == redir)\ni = %i\ninstruction[i] = %c\n", i, instructions[i]);)
			}
			count_redirs++;
		}
		else
		{
			DEBUG(printf("else\ni = %i\ninstruction[i] = %c\n", i, instructions[i]);)
			i++;
			DEBUG(printf("end_boucle\ni = %i\ninstruction[i] = %c\n", i, instructions[i]);)
		}
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