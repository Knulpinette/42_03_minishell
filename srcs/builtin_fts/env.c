#include "minishell.h"

/*
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
