#include "minishell.h"

void	parse(char *line)
{
	t_minishell	*minishell;

	minishell = get_minishell(NULL);
	minishell->input = ft_split(line, PIPE);
	minishell->nb_cmd = get_split_len(minishell->input);
	init_cmd_table_and_tokens();
	
	// get command
	// skip space
	// until it doesn't start by '-' + alphanumerical (until stop alphanumerical, get flag
	// skip space
	// check redir
	// check quote
	// save arg
	free_split(minishell->input); 
	return ;
}

void	init_cmd_table_and_tokens()
{
	t_minishell	*minishell;
	int			nb_cmd;
	int			i;

	minishell = get_minishell(NULL);
	nb_cmd = minishell->nb_cmd;
	minishell->cmd_table = calloc_or_exit(sizeof(t_cmd_table *), nb_cmd + 1);
	i = 0;
	while (i < nb_cmd)
	{
		minishell->cmd_table[i] = calloc_or_exit(sizeof(t_cmd_table), 1);
		minishell->cmd_table[i]->tokens = ft_split(minishell->input[i], SPACE);
		DEBUG(print_split(minishell->cmd_table[i]->tokens);)
		i++;
	}
	minishell->cmd_table[i] = 0;
}
