#include "minishell.h"

void	setup_all_variables_with_dbl_quotes_exception(
			t_token *token, char **env_var, int *len_token)
{
	char	*starting_point;
	int		env_var_len;

	*env_var = NULL;
	*len_token = ft_strlen(token->text) - 2;
	if (ft_strchr(token->text, '$') && token->quote == DBL_QUOTE)
	{
		starting_point = ft_strchr(token->text, '$') + 1;
		env_var_len = get_env_var_len(token->text, DBL_QUOTE);
		*env_var = get_env_var(starting_point, env_var_len, DBL_QUOTE);
		*len_token = (*len_token) - env_var_len + ft_strlen(*env_var); 
	}
}

void	remove_quotes(t_token *token)
{
	char	*temp;
	char	*env_var;
	int		len_token;
	int		i;
	int		j;

	setup_all_variables_with_dbl_quotes_exception(token, &env_var, &len_token);
	temp = calloc_or_exit(sizeof(char), len_token + 1);
	i = 0;
	j = 0;
	while (token->text[i])
	{
		if (token->text[i] == '$' && token->quote == DBL_QUOTE)
		{
			i = i + get_env_var_len(token->text, DBL_QUOTE);
			j = j + ft_strlcpy(&temp[j], env_var, ft_strlen(env_var) + 1);
		}
		else if (token->text[i] != token->quote)
			temp[j++] = token->text[i];
		i++;
	}
	if (env_var)
		free(env_var);
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

static int	get_flags_count(t_token *tokens, int nb_tokens)
{
	int count;
	int	i;

	count = 0;
	i = 0;
	while (i < nb_tokens)
	{
		if (tokens[i].type == FLAG)
			count++;
		i++;
	}
	return (count);
}

void	assign_tokens(t_cmd_table *cmd_table)
{
	int	i;
	int	j;
	int f;
	int	nb_args;
	int	nb_flags;

	i = 0;
	j = 0;
	f = 0;
	nb_args = get_args_count(cmd_table->tokens, cmd_table->nb_tokens);
	cmd_table->cmd_args = calloc_or_exit(sizeof(char *), nb_args + 1);
	nb_flags = get_flags_count(cmd_table->tokens, cmd_table->nb_tokens);
	cmd_table->flags = calloc_or_exit(sizeof(char*), nb_flags + 1);
	while (i < cmd_table->nb_tokens)
	{
		if (cmd_table->tokens[i].type == CMD)
			cmd_table->cmd_name = cmd_table->tokens[i].text;
		else if (cmd_table->tokens[i].type == FLAG)
			cmd_table->flags[f++] = cmd_table->tokens[i].text;
		else if (cmd_table->tokens[i].type == WORD)
			cmd_table->cmd_args[j++] = cmd_table->tokens[i].text;
		i++;
	}
	if (nb_args)
		cmd_table->cmd_args[j] = 0;
	if (nb_flags)
		cmd_table->flags[f] = 0;
	return ;
}
