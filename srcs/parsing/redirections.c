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
		//DEBUG(printf("while (instructions[i])\ni = %i\ninstruction[i] = %c\nquote = %c\n", i, instructions[i], quote);)
		if ((instructions[i] == '<' || instructions[i] == '>') && !quote)
		{
			//DEBUG(printf("if ((instructions[i] == '<' || instructions[i] == '>') && !quote)\ni = %i\ninstruction[i] = %c\n", i, instructions[i]);)
			redir = instructions[i];
			i++;
			//DEBUG(printf("i++;\ni = %i\ninstruction[i] = %c\n", i, instructions[i]);)
			if (instructions[i] && instructions[i] == redir)
			{
				i++;
			//	DEBUG(printf("if (instructions[i] && instructions[i] == redir)\ni = %i\ninstruction[i] = %c\n", i, instructions[i]);)
			}
			count_redirs++;
		}
		else
		{
			//DEBUG(printf("else\ni = %i\ninstruction[i] = %c\n", i, instructions[i]);)
			i++;
			//DEBUG(printf("end_boucle\ni = %i\ninstruction[i] = %c\n", i, instructions[i]);)
		}
	}
	DEBUG(printf("count of redirs = %i\n", count_redirs);)
	return (count_redirs);
}

static t_redir_type	get_redir_type(const char *instructions, int i)
{
	t_redir_type	redir_type;
	int				redir;

	redir = instructions[i];
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

static char			*save_next_word_as_arg(const char *instructions, int i)
{
	char	*arg;
	char	quote;
	int		arg_len;
	int		j;

	arg_len = 0;
	quote = 0;
	while (instructions[i] == SPACE)
		i++;
	while (instructions[i + arg_len] && (instructions[i + arg_len] != SPACE && !quote))
	{
		quote = check_quote(instructions[i + arg_len], quote);
		arg_len++;
	}
	//DEBUG(printf("while (instructions[i + arg_len])\narg_len = %i\n", arg_len);)
	arg = calloc_or_exit(sizeof(char), arg_len + 1);
	j = 0;
	while (instructions[i] && j < arg_len)
		arg[j++] = instructions[i++];
	arg[j] = 0;
	return (arg);
}

t_redir				*get_redirs(const char *instructions, int nb_redirs)
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
			redirs[count].type = get_redir_type(instructions, i);
			if (redirs[count].type == OP_REDIR_IN || redirs[count].type == OP_REDIR_OUT)
				i += 1;
			else if (redirs[count].type == OP_DELIMITER || redirs[count].type == OP_APPEND)
				i += 2;
			redirs[count].arg = save_next_word_as_arg(instructions, i);
			i += ft_strlen(redirs[count].arg);
			//DEBUG(printf("i+= ft_strlen(redirs[count].arg)\ni = %i\n", i);)
			count++;
		}
		else
			i++;
	}
	return (redirs);
}
