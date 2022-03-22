#include "minishell.h"

/*
 * Error handling
 * Export without options - thus it will ignore any flags
 * and not throw out an error
 */

int	export(t_cmd_table *cmd, t_minishell *minishell)
{
	(void)minishell;

	if (!cmd->cmd_args[0])
	{
		// sort - a linkedlist... fuck. or. I can just print in order?
		// print "declare -x "
		// print env
		// understand difference between assigned and unassigned env vars
		return (0);
	}
	// add the new var to the list - this is actually simpler
	// check if there's a limit to nb of arguments it can handle
	// error handling with wrong args
	return (0);
}
