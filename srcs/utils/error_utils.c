#include "minishell.h"

int		error_and_exit(t_error code)
{
	t_minishell *minishell;

	minishell = get_minishell(NULL);
	error_message(code);
	if (minishell)
		free_minishell(minishell);
	exit(EXIT_FAILURE);
}

void	error_message(t_error code)
{
	if (MEMORY_FAIL) //in the meantime before linking libft. 
		printf("%s\n", strerror(errno)); // don't forget to print on STDERR_FILENO
}
