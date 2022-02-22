#include "minishell.h"

void	parse(char *line)
{
	t_minishell	*minishell;
	//int			i;
	//char		**tokens;

	//i = 0;
	minishell = get_minishell(NULL);
	minishell->input = ft_split(line, PIPE);
	minishell->nb_cmd = get_nb_split(minishell->input);
	/*minishell->cmd_table = calloc_or_exit(sizeof(t_cmd_table *), minishell->nb_cmd + 1);
	while (i < minishell->nb_cmd)
	{
		DEBUG(printf("i = %i\n", i);)
		minishell->cmd_table[i]->infile_fd = i;
		printf("infile = %i\n", minishell->cmd_table[0]->infile_fd);
		//tokens = ft_split(minishell->input[i], SPACE);
		//DEBUG(print_split(tokens);)
		i++;
	}*/
	//divide in cmd_tables
	// skip space
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
