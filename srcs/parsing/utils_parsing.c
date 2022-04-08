#include "minishell.h"

bool			is_not_exception(char letter, t_token_type type)
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

int				pass_space(char *text)
{
	int	count;

	count = 0;
	while (text[count] && text[count] == SPACE)
		count++;
	return (count);
}

int				pass_redir(char *instruction)
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
	while (instruction[count] && ((!quote &&
			is_not_exception(instruction[count], REDIR)) || quote))
	{
		quote = check_quote(instruction[count], quote);
		count++;
	}
	return (count);
}

bool			text_is_all_n(char *text)
{
	int	i;

	i = 0;
	while (text[i])
	{
		if (text[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

t_token_type	handle_special_case_echo(t_token *tokens, int i)
{
	if (i == 1 && (tokens[i].text[0] == '-' && text_is_all_n(tokens[i].text + 1)))
		return (FLAG);
	return (WORD);
}
