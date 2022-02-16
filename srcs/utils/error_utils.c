#include "minishell.h"

int		error_and_exit(t_error code)
{
	t_minishell *minishell;

	minishell = get_minishell(NULL);
	error_message(code); // later on, maybe add the program_pathname stored in struct to print a clearer error
	if (minishell)
		free_minishell(minishell);
	exit(EXIT_FAILURE);
}

void	error_message(t_error code)
{
	if (code == ERR_NO_PRINT)
		return ;
	// we could print the program name here
	if (MEMORY_FAIL) //in the meantime before linking libft. 
		printf("%s\n", strerror(errno)); // don't forget to print on STDERR_FILENO
}
