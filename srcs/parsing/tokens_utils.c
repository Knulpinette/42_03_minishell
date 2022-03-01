#include "minishell.h"

void	remove_quotes(t_token *token)
{
	char	*temp;
	int		len;
	int		i;
	int		j;

	/*if (token->quote == DBL_QUOTE && ft_strchr(token->text, '$'))
	{
		int	env_var_count;

		len = strlen(token->text) - 2;
		skip_to_$;
		get_env_var_count until '"';
		len = len - env_var_count;
		get env_var;
		len = len + ft_strlen(env_var);
		temp = calloc_or_exit(sizeof(char), len);
		i = 0;
		while (token->text[i])
		{
			if (token->text[i] == '$')
			{
				append_env_var to temp;
				i = i + env_var_count;
			}
			if (token->text[i] != token->quote)
			temp[j++] = token->text[i];
			i++;
		}
		free(token->text);
		token->text = strdup(temp);
		free(temp); 
		return ;
	}*/
	len = ft_strlen(token->text) - 2;
	temp = calloc_or_exit(sizeof(char), len + 1);
	i = 0;
	j = 0;
	while (token->text[i])
	{
		if (token->text[i] != token->quote)
			temp[j++] = token->text[i];
		i++;
	}
	free(token->text);
	token->text = strdup(temp);
	free(temp); 
}

void	get_tokens_types(t_token *tokens, int nb_tokens)
{
	int	i;

	i = 0;
	while (i < nb_tokens)
	{
		if (tokens[i].quote)
			remove_quotes(&tokens[i]);
		//check_for_redir => get all info and go along the right amount of tokens
		//then => next token == cmd
		if (i == 0)
			tokens[i].type = CMD;
		else if (tokens[i].text[0] == '-' && tokens[i].text[1])
			tokens[i].type = FLAG;
		else if (ft_strchr(tokens[i].text, '$') && tokens[i].quote != SGL_QUOTE)
			tokens[i].type = ENV_VAR;
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
