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
	ft_putstr_fd(cwd, cmd->fd_out); // TODO change once the redirs are in place
	write(cmd->fd_out, "\n", 1);
	free(cwd);
	return (0);
}
