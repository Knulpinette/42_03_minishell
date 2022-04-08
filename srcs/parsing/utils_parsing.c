#include "minishell.h"

bool	is_not_exception(char letter, t_token_type type)
{
	if (letter == SPACE)
		return (false);
	else if (type == ENV_VAR && letter == '$')
		return (false);
	else if (type == ENV_VAR && letter == DBL_QUOTE)
		return (false);
	else if (letter == '>')
		return (false);
	else if (letter == '<')
		return (false);
	else
		return (true);
}

int	pass_space(char *text)
{
	int	count;

	count = 0;
	while (text[count] && text[count] == SPACE)
		count++;
	return (count);
}

int	pass_redir(char *instruction)
{
	int		count;
	char	redir;
	char	quote;

	count = 0;
	quote = 0;
	redir = instruction[count++];
	if (instruction[count] && instruction[count] == redir)
		count++;
	count += pass_space(instruction + count);
	while (instruction[count] && instruction[count] != SPACE && !quote)
	{
		quote = check_quote(instruction[count], quote);
		count++;
	}
	return (count);
}
