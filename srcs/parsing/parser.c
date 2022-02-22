#include "minishell.h"

void	parse(char *line)
{
	t_minishell	*minishell;

	minishell = get_minishell(NULL);
	minishell->input = ft_split(line, PIPE);
	minishell->nb_cmd = get_nb_split(minishell->input);
	//divide in cmd_tables
	// skip space
	// get command
	// skip space
	// until it doesn't start by '-' + alphanumerical (until stop alphanumerical, get flag
	// skip space
	// check redir
	// check quote
	// save arg
	DEBUG(print_split(minishell->input);)
	//free_split(minishell->input); // voir pourquoi problème.
	return ;
}
