#include "minishell.h"

static t_token_type	handle_special_case_echo(t_token *tokens, int i)
{
	if (i == 1 && (tokens[i].text[0] == '-' && text_is_all_n(tokens[i].text + 1)))
		return (FLAG);
	return (WORD);
}

void				get_tokens_types(t_token *tokens, int nb_tokens)
{
	int		i;
	bool	cmd_is_echo;

	i = 0;
	cmd_is_echo = false;
	while (i < nb_tokens)
	{
		if (there_is_quote(tokens[i].text, DBL_QUOTE) ||
				there_is_quote(tokens[i].text, SGL_QUOTE))
			tokens[i].text = remove_quotes(tokens[i].text);
		if (cmd_is_echo)
			tokens[i].type = handle_special_case_echo(tokens, i);
		else if (i == 0)
		{
			tokens[i].type = CMD;
			if (ft_strncmp(tokens[i].text, "echo", 4) == 0)
				cmd_is_echo = true;
		}
		else if (tokens[i].text[0] == '-' && ft_isprint(tokens[i].text[1]))
			tokens[i].type = FLAG;
		else
			tokens[i].type = WORD;
		i++;
	}
	return ;
}	

static int			get_type_count(t_token *tokens, int nb_tokens, t_token_type type)
{
	int count;
	int	i;

	count = 0;
	i = 0;
	while (i < nb_tokens)
	{
		if (tokens[i].type == type)
			count++;
		i++;
	}
	return (count);
}

static char			**get_args(t_token *tokens, int nb_tokens, t_token_type arg_type)
{
	int		i;
	int		j;
	int		nb_args;
	char	**args;

	i = 0;
	j = 0;
	nb_args = get_type_count(tokens, nb_tokens, arg_type);
	args = calloc_or_exit(sizeof(char*), nb_args + 1);
	while (i < nb_tokens)
	{
		if (tokens[i].type == arg_type)
			args[j++] = tokens[i].text;
		i++;
	}
	args[j] = 0;
	return (args);
}

void				assign_tokens(t_cmd_table *cmd_table)
{
	int	i;

	i = 0;
	while (i < cmd_table->nb_redirs)
	{
		/*if (!cmd_table->redirs[i].arg)
			error_and_exit(REDIR_SYNTAX_ERROR);*/
		if (there_is_quote(cmd_table->redirs[i].arg, DBL_QUOTE) ||
				there_is_quote(cmd_table->redirs[i].arg, SGL_QUOTE))
			cmd_table->redirs[i].arg = remove_quotes(cmd_table->redirs[i].arg);
		i++;
	}
	cmd_table->cmd_name = cmd_table->tokens[0].text;
	cmd_table->flags = get_args(cmd_table->tokens, cmd_table->nb_tokens, FLAG);
	cmd_table->cmd_args = get_args(cmd_table->tokens, cmd_table->nb_tokens, WORD);
}