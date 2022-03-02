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

t_minishell		*init_minishell(char **envp)
{
	t_minishell *minishell;

	minishell = calloc_or_exit(sizeof(t_minishell), 1);
	get_minishell(minishell);
	minishell->nb_cmd = 0;
	minishell->instructions = NULL;
	minishell->envp = envp;
	minishell->envp_paths = get_cmd_paths(envp);
	minishell->cmd_table = NULL;
	return (minishell);
}

void	*calloc_or_exit(size_t size, int count)
{
	void	*result;

	result = ft_calloc(size, count);
	if (!result)
		error_and_exit(MEMORY_FAIL);
	return (result);
}
