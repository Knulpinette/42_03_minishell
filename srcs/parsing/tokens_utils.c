#include "minishell.h"

void	remove_quotes(t_token *token)
{
	char	*temp;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(token->text) - 2;
	if (token->quote == DBL_QUOTE && ft_strchr(token->text, '$'))
	{
		int	env_var_count;
		char	*real_var;
		char	*env_var;

		while (token->text[i] != '$')
			i++;
		// MAKE SEPARATE FUNCTION FOR THIS
		i++;
		env_var_count = 0;
		while (token->text[i + env_var_count] != DBL_QUOTE)
			env_var_count++;
		env_var = calloc_or_exit(sizeof(char), env_var_count + 1);
		while (token->text[i] != DBL_QUOTE)
			env_var[j++] = token->text[i++];
		env_var[j] = 0;
		real_var = strdup(getenv(env_var));
		//if error, handle
		DEBUG(printf("%s\n", real_var);)
		free(env_var);
		len = len - env_var_count + ft_strlen(real_var);
		temp = calloc_or_exit(sizeof(char), len);
		i = 0;
		j = 0;
		while (token->text[i]) // error here of buffer overflow
		{
			if (token->text[i] == '$')
			{
				len = ft_strlcpy(&temp[j], real_var, ft_strlen(real_var) + 1);
				i = i + env_var_count;
				j = j + ft_strlen(real_var);
			}
			else if (token->text[i] != token->quote)
				temp[j++] = token->text[i];
			i++;
		}
		free(real_var);
		free(token->text);
		token->text = strdup(temp);
		free(temp); 
		return ;
	}
	temp = calloc_or_exit(sizeof(char), len + 1);
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
