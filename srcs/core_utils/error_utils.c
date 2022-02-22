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
	if (code == WRONG_ARGC)
		ft_putstr_fd("Wrong number of arguments.\n", 2);
	if (code == MEMORY_FAIL || code == OPEN_FAIL)
	{
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
	}
}

int	open_or_exit(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		error_and_exit(OPEN_FAIL);
	return (fd);
}
