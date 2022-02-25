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
	if (code == ERR_NO_PRINT)
		return ;
	ft_putstr_fd(""LIGHT_RED"Error \n"END_COLOR"", STDERR_FILENO);
	if (code == WRONG_ARGC)
		ft_putstr_fd("Wrong number of arguments.\n", STDERR_FILENO);
	if (code == MEMORY_FAIL || code == OPEN_FAIL)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		write(STDERR_FILENO, "\n", 1);
	}
}

int	open_or_exit(char *file_path, mode_t mode)
{
	int	fd;

	fd = open(file_path, mode);
	if (fd == -1)
		error_and_exit(OPEN_FAIL);
	return (fd);
}
