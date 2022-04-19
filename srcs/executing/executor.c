#include "minishell.h"

/*
** Case to check later (no command) : 
	> hello | ls -l
See if it still segfaults when proper executor is built! 
*/


/*
 * 1. PIPES
 *	If there's a next command, open the pipe
 *	Update fd_out from current command and fd_in from next command
 *
 * 2. REDIRECTIONS
 *	Closes previous fd_in/out if not stdin/out (so pipe and other redirection)
 *	Opens the new one
 *	If something happens we're out with exit_code 1
 *
 * 3. NO CMD
 *	If there's no command, we're out with exit_code 0
 *
 * 4. BUILT-IN
 *	If the function is built-in, call it and update exit_code
 *
 * 5. NON-BUILT-IN
 *
 * X. CLOSING
 *	If fd_in != stdin close it, if fd_out != stdout close it
 *	Right now, no matter how many pipes or redirections we have, we never go above fd 5
 *
 * Z. ERROR HANDLING
 *	- if pipe or close functions return an error, we exit
 *	- if open function returns an error, we display message and go to next command
 *	  as it might be because the file doesn't exist (pretty common error)
 */

static void	close_for_next_cmd(t_cmd_table cmd)
{
	if (cmd.fd_in != 0)
		close(cmd.fd_in);
	if (cmd.fd_out != 1)
		close(cmd.fd_out);
}

int	execute(t_minishell *minishell)
{
	int	i;
	int	fd[2];

	i = 0;
	while (i < minishell->nb_cmds)
	{
		minishell->exit_code = 0;
		if (i + 1 < minishell->nb_cmds)
		{
			if (pipe(fd) == -1)
				error_and_exit(PIPE_FAIL);
			minishell->cmd_table[i].fd_out = fd[1];
			minishell->cmd_table[i + 1].fd_in = fd[0];
		}
		if ((minishell->exit_code = exec_redirs(&minishell->cmd_table[i]))
			|| !minishell->cmd_table[i].cmd_name)
		{
			close_for_next_cmd(minishell->cmd_table[i++]);
			continue;
		}
		DEBUG(printf("Redir In: %d, Redir Out: %d\n", minishell->cmd_table[i].fd_in, minishell->cmd_table[i].fd_out));
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
		// swap stdin/out with fd_in/out -> aftert the fork? we don't want to change stdout/in in main process...
		// fork and call execve -> how to get exit code from it? (check goncalo tuto)

		// error handling: if at some point something happens... still need to close stuff
		// and update exit code

		close_for_next_cmd(minishell->cmd_table[i]);
		i++;
	}
	return (minishell->exit_code);
}
