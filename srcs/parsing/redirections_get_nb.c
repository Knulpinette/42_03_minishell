#include "minishell.h"

bool	is_quote(char letter, char quote)
{
	if (letter == quote)
		return (true);
	return (false);
}

int	pass_quotes(char *instructions, int i, char quote)
{
	int	count;

	count = 0;
	//DEBUG(printf("pass quotes begins at : %s || char = %c\n", instructions + i + count, instructions[i + count]);)
	while (instructions[i + count] && !is_quote(instructions[i + count], quote))
		count++;
	//DEBUG(printf("pass quotes ends on : %s || char = %c\n", instructions + i + count, instructions[i + count]);)
	if (instructions[i + count] == quote)
		return (count + i);
	else
		return (i - 1);
}

int	get_nb_redirs(char *instructions)
{
	int		count;
	int		i;
	char	quote;
	char	redir;

	count = 0;
	i = 0;
	quote = 0;
	redir = 0;
	while (instructions[i])
	{
		if (instructions[i] == SGL_QUOTE || instructions[i] == DBL_QUOTE)
		{
			quote = instructions[i];
			i = pass_quotes(instructions, i + 1, quote) + 1;
			//DEBUG(printf("sending in loop : %s || char = %c\n", instructions + i, instructions[i]);)
		}
		else if (instructions[i] == '<' || instructions[i] == '>')
		{
			redir = instructions[i];
			i++;
			if (instructions[i] && instructions[i] == redir)
				i++;
			count++;
		}
		else
			i++;
	}
	//DEBUG(printf("count of redirs = %i\n", count);)
	return (count);
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