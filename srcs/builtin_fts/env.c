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
	t_list	*curr;

	curr = minishell->env;
	while (curr)
	{
		if (get_env_lst_value(curr))
		{
			ft_putstr_fd(get_env_lst_name(curr), cmd->fd_in);
			write(cmd->fd_in, "=", 1);
			ft_putstr_fd(get_env_lst_value(curr), cmd->fd_in);
			write(cmd->fd_in, "\n", 1);
		}
		curr = curr->next;
	}
	return (0);
}
