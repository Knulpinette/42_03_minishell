#include "minishell.h"

/*
 * Acessing env variables
 * - envp from main
 * - extern char **environ from unistd.h
 * - getenv("VAR_NAME") for the value of a specific variable
 *
 * However, I decided to do a separate env linked list,
 * so that's the one we actually need to access
 *
 * Error Handling
 * No need to handle options nor arguments as per the subject
 */

int	env(t_cmd_table *cmd, t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->envp[i])
	{
		ft_putstr_fd(minishell->envp[i], cmd->fd_in);
		write(cmd->fd_in, "\n", 1);
		i++;
	}
	return (0);
}
