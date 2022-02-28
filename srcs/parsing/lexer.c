#include "minishell.h"

void	lexer(char *line)
{
	t_minishell	*minishell;
	int	i;

	minishell = get_minishell(NULL);
	minishell->instructions = ft_split(line, PIPE);
	minishell->nb_cmd = get_array_len(minishell->instructions);
	minishell->cmd_table = init_cmd_table(minishell->nb_cmd);
	i = 0;
	while (i < minishell->nb_cmd)
	{
		minishell->cmd_table[i].nb_tokens = get_nb_tokens(minishell->instructions[i], SPACE);
		minishell->cmd_table[i].tokens =
			get_tokens(minishell->instructions[i], SPACE, minishell->cmd_table[i].nb_tokens);
		//get_tokens_types();
		i++;
	}
	free_split(minishell->instructions);
}

/*
void	get_token_types()
{
	if (SGL_QUOTE)
		remove_quote + WORD;
	if (DBL_QUOTE)
		remove_quote + deal with ENV_VAR;
	if (1rst Token)
		CMD;
	else if (-something)
		FLAG;
	else if ($)
		ENV_VAR;
	else if (> < >> <<)
		REDIRECTION;
	else
		WORD;
}	
*/