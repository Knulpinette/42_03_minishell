#include "minishell.h"

/*
 * Error Handling
 * In bash, arguments are ignored.
 * In zsh it says "pwd: too many arguments".
 */

int	pwd(t_cmd_table *cmd)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	ft_putstr_fd(cwd, cmd->fd_in); // change once the struct is in place
	write(cmd->fd_in, "\n", 1);
	free(cwd);
	return (0);
}