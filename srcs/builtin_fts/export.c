#include "minishell.h"

/*
 * Error handling
 * Export without options - thus it will ignore any flags
 * and not throw out an error
 */

void	print_export( t_list *env, int fd_in)
{
	while (env)
	{
		ft_putstr_fd("declare -x ", fd_in);
		ft_putstr_fd(get_env_lst_name(env), fd_in);
		write(fd_in, "=\"", 2);
		ft_putstr_fd(get_env_lst_value(env), fd_in);
		write(fd_in, "\"\n", 2);
		env = env->next;
	}
}

int	export(t_cmd_table *cmd, t_minishell *minishell)
{
	t_list	*sorted_env;

	if (!cmd->cmd_args[0])
	{
		sorted_env = copy_env_lst(minishell->env);
		merge_sort(&sorted_env);
		print_export(sorted_env, cmd->fd_in);
		// understand difference between assigned and unassigned env vars
		ft_lstclear(&sorted_env, &del_env_content);
		return (0);
	}
	// add the new var to the list - this is actually simpler
	// check if there's a limit to nb of arguments it can handle
	// error handling with wrong args
	return (0);
}
