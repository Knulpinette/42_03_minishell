#include "minishell.h"

/*
** 🦕🌴
**
** get_redirs
**
**	Redirections are as follow
**		>	will redirect the std_input to a given file
**		<	will redirect the std_output to a given file
**		>>	will append the std_input to the given fd
**		<<	will save the std_input until it finds the given delimiter
**	1. We get the number of redirections to init the struct properly
**	2. We extract the right redir_type to give to the individual redir.
**	3. We save the 'word' following the redir_operator as the argument.
**		That 'word' ends when encountering a SPACE, '<' or '>'.
**
** 🌴🥥
*/

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
	return (count_redirs);
}

static t_redir_type	get_redir_type(const char *instructions, int i)
{
	t_redir_type	redir_type;
	int				redir;

	redir = instructions[i];
	redir_type = 0;
	i++;
	if (instructions[i] && instructions[i] == redir)
	{
		if (redir == '<')
			redir_type = OP_DELIMITER;
		else if (redir == '>')
			redir_type = OP_APPEND;
		i++;
	}
	else
	{
		if (redir == '<')
			redir_type = OP_REDIR_IN;
		else if (redir == '>')
			redir_type = OP_REDIR_OUT;
	}
	return (redir_type);
}

static char	*save_next_word_as_arg(const char *instructions, int i)
{
	char	*arg;
	char	quote;
	int		arg_len;
	int		j;

	arg_len = 0;
	quote = 0;
	while (instructions[i] == SPACE)
		i++;
	while (instructions[i + arg_len]
		&& ((!quote && is_not_exception(instructions[i + arg_len], REDIR))
			|| quote))
	{
		quote = check_quote(instructions[i + arg_len], quote);
		arg_len++;
	}
	arg = calloc_or_exit(sizeof(char), arg_len + 1);
	j = 0;
	while (instructions[i] && j < arg_len)
		arg[j++] = instructions[i++];
	arg[j] = 0;
	return (arg);
}

// THIS FUNCTION HAS MORE THAN 25 LINES !!

static int	parse_redir(t_redir *redirs, const char *instructions, int i)
{
	int	len_parse;

	len_parse = 0;
	redirs->type = get_redir_type(instructions, i);
	if (redirs->type == OP_REDIR_IN
		|| redirs->type == OP_REDIR_OUT)
		len_parse += 1;
	else if (redirs->type == OP_DELIMITER
		|| redirs->type == OP_APPEND)
		len_parse += 2;
	redirs->arg = save_next_word_as_arg(instructions, i + len_parse);
	len_parse += ft_strlen(redirs->arg);
	return (len_parse);
}

t_redir	*get_redirs(const char *instructions, int nb_redirs)
{
	t_redir	*redirs;
	int		i;
	int		count;
	char	quote;

	if (!instructions)
		return (NULL);
	redirs = calloc_or_exit(sizeof(t_redir), nb_redirs);
	i = 0;
	count = 0;
	quote = 0;
	while (instructions[i] && count < nb_redirs)
	{
		quote = check_quote(instructions[i], quote);
		if ((instructions[i] == '<' || instructions[i] == '>') && !quote)
		{
			i += parse_redir(&redirs[count], instructions, i);
			count++;
		}
		else
			i++;
	}
	return (redirs);
}
