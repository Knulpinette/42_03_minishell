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

// handle problem of removing extra quote if "yo""this""hello

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
		//voir si garder remove_quotes tel quel. Pas ouf + problème potentiel env_var? => needs to set up env_var int in the struct!
       /* if (ft_strchr(tokens[i].text, '$') && tokens[i].quote != SGL_QUOTE) //pbme of tokens that would be like this 'yo'$OUT ? => need to handle that. Use a quote_count = 0, 1, 2 ?
        {
            tokens[i].env_var = ENV_VAR;
            tokens[i].type = ENV_VAR;
        }*/
        //if ('$' => set tokens[i].env_var = ENV_VAR)
            //replace with get_env_var (WHEN VALIDATION OR ASSIGNING TOKEN TYPES => every single part of it needs to become an argument => cut it & have a special case for if it's a CMD)
        //check_for_redir => get all info and go along the right amount of tokens
        //then => next token == cmd

		//check_for_redir => get all info and go along the right amount of tokens
		//then => next token == cmd
		if (i == 0)
			tokens[i].type = CMD;
		else if (tokens[i].text[0] == '-' && tokens[i].text[1])
			tokens[i].type = FLAG;
		else
			tokens[i].type = WORD;
		i++;
	}
	return ;
}	
