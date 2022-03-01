#include "minishell.h"

void	get_tokens_types(t_token *tokens, int nb_tokens)
{
	int	i;

	i = 0;
	while (i < nb_tokens)
	{
		/*if (tokens[i].quote)
			handle_quotes;
			if (SGL_QUOTE)
				remove_quote + WORD;
			if (DBL_QUOTE)
			remove_quote + deal with ENV_VAR;
		else*/ if (i == 0)
			tokens[i].type = CMD;
		else if (tokens[i].text[0] == '-')
			tokens[i].type = FLAG;
		else if (ft_strchr(tokens[i].text, '$'))
			tokens[i].type = ENV_VAR;
		else if (ft_strchr(tokens[i].text, '<'))
		{ 
			// redir peuvent être collées au texte ?
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

static int	get_args_count(t_token *tokens, int nb_tokens)
{
	int count;
	int	i;

	count = 0;
	i = 0;
	while (i < nb_tokens)
	{
		if (tokens[i].type == WORD)
			count++;
		i++;
	}
	return (count);
}

void	assign_tokens(t_cmd_table *cmd_table)
{
	int	i;
	int	j;
	int	nb_args;

	i = 0;
	j = 0;
	nb_args = get_args_count(cmd_table->tokens, cmd_table->nb_tokens);
	cmd_table->cmd_args = calloc_or_exit(sizeof(char *), nb_args + 1);
	while (i < cmd_table->nb_tokens)
	{
		if (cmd_table->tokens[i].type == CMD)
			cmd_table->cmd_name = cmd_table->tokens[i].text;
		else if (cmd_table->tokens[i].type == WORD)
			cmd_table->cmd_args[j++] = cmd_table->tokens[i].text;
		i++;
	}
	if (nb_args)
		cmd_table->cmd_args[j] = 0;
	return ;
}
