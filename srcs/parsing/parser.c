#include "minishell.h"

void	parse(char *line)
{
	t_minishell	*minishell;

	minishell = get_minishell(NULL);
	minishell->instructions = ft_split(line, PIPE);
	minishell->nb_cmd = get_split_len(minishell->instructions);
	minishell->cmd_table = init_cmd_table(minishell->nb_cmd);
	// make token struct with key/type etc.
	// get command
	// skip space
	// until it doesn't start by '-' + alphanumerical (until stop alphanumerical, get flag
	// skip space
	// check redir
	// check quote
	// save arg
	free_split(minishell->instructions); 
	return ;
}

t_cmd_table	**init_cmd_table(int nb_cmd)
{
	t_cmd_table	**cmd_table;
	int			i;

	cmd_table = calloc_or_exit(sizeof(t_cmd_table *), nb_cmd + 1);
	i = 0;
	while (i < nb_cmd)
	{
		cmd_table[i] = calloc_or_exit(sizeof(t_cmd_table), 1);
		cmd_table[i]->tokens = NULL;
		cmd_table[i]->cmd = NULL;
		cmd_table[i]->flags = NULL;
		cmd_table[i]->cmd_path = NULL;
		cmd_table[i]->infile_fd = STDIN_FILENO;
		cmd_table[i]->infile = NULL;
		cmd_table[i]->outfile_fd = STDOUT_FILENO;
		cmd_table[i]->outfile = NULL;
		cmd_table[i]->delimiter = false;
		cmd_table[i]->delim_arg = NULL;
		cmd_table[i]->mode = OVERWRITE;
		cmd_table[i]->cmd_arg = NULL;
		i++;
	}
	cmd_table[i] = 0;
	return (cmd_table);
}
