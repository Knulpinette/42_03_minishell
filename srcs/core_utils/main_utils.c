#include "minishell.h"

/* cool concept (singleton) taken from Michele who didn't use any global variables. 
 This allow us to store the pointer of minishell once and be able to
 reaccess it any point in our code, without passing the struct. 	*/
t_minishell		*get_minishell(t_minishell *minishell)
{
	static t_minishell	*pointer_to_minishell = NULL;

	if (!pointer_to_minishell && minishell)
		pointer_to_minishell = minishell;
	return (pointer_to_minishell);
}

t_minishell		*init_minishell()
{
	t_minishell minishell;
	t_cmd_table *init;
	
	minishell.cmd_table = ft_calloc(sizeof(char *), 1);
	if (!minishell.cmd_table)
		error_and_exit(MEMORY_FAIL);
	init = &minishell.cmd_table[0];
	init->infile_fd = 0;
	init->outfile_fd = 0;
	init->delimiter = false;
	init->mode = OVERWRITE;
	init->args = ft_calloc(sizeof(char *), 1);
	if (!init->args)
		error_and_exit(MEMORY_FAIL);
	return (get_minishell(&minishell));
}