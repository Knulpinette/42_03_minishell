#include "minishell.h"

/*
** Case to check later (no command) : 
	> hello | ls -l
See if it still segfaults when proper executor is built! 
*/

int	execute(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (i < minishell->nb_cmds)
	{
		// if there's a next command
		// open the pipe
		// change fd_out and fd_int from next command
		//
		// if there's redirections
		// loop over them (nb_redirs)
		// close the previous if we opened one in the previous loop
		// -- redir_in_open and redir_out_open booleans
		// open the file - create it if non-existant and it's redir_out!
		// change fd_in and/or fd_out accordingly
		// the fuck about delimiter
		if (!minishell->cmd_table[i].cmd_name)
		{
			i++;
			continue;
		}
		// if it's a builtin function -> aux function that returns which function it is?
		// execute built-in function:
		// can it be more elegant than this, or... not really?
		if (ft_strncmp(minishell->cmd_table[i].cmd_name, "cd", 2) == 0)
			minishell->exit_code = cd(&minishell->cmd_table[i]);
		else if (ft_strncmp(minishell->cmd_table[i].cmd_name, "pwd", 3) == 0)
			minishell->exit_code = pwd(&minishell->cmd_table[i]);
		else if (ft_strncmp(minishell->cmd_table[i].cmd_name, "env", 3) == 0)
			minishell->exit_code = env(&minishell->cmd_table[i], minishell);
		else if (ft_strncmp(minishell->cmd_table[i].cmd_name, "echo", 4) == 0)
			minishell->exit_code = echo(&minishell->cmd_table[i]);
		else if (ft_strncmp(minishell->cmd_table[i].cmd_name, "export", 6) == 0)
			minishell->exit_code = export(&minishell->cmd_table[i], minishell);
		else if (ft_strncmp(minishell->cmd_table[i].cmd_name, "unset", 5) == 0)
			minishell->exit_code = unset(&minishell->cmd_table[i], minishell);
		
		// else if not built-in
		// check if command exists and flags are appropriate with access (check discord)
		// swap stdin/out with fd_in/out
		// fork and call execve -> how to get exit code from it? (check goncalo tuto)

		// error handling: if at some point something happens... still need to close stuff
		// and update exit code

		// close writing end of pipe and fd_out file if needed?
		// how to know if it's needed? has_pipe and has_redir booleans?
		i++;
	}
	return (minishell->exit_code);
}
