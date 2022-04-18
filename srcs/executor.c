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
 * X. CLOSING
 *	if fd_in != stdin close it, if fd_out != stdout close it
 *
 * Z. ERROR HANDLING
 *	- if pipe, open or close functions return an error, we exit
 */

void	execute_redirections(t_cmd_table *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->nb_redirs)
	{
		if (cmd.redirs[i].type == OP_REDIR_IN)
		{
			if (cmd.fd_in != 0 && close(cmd.fd_in) == -1)
				error_and_exit(CLOSE_FAIL);
			cmd.fd_in = open_or_exit(cmd.redirs[i].arg, O_RDWR);
		}
		else if (cmd.redirs[i].type == OP_REDIR_OUT || cmd.redirs[i].type == OP_APPEND)
		{
			if (cmd.fd_out != 1 && close(cmd.fd_out) == -1)
				error_and_exit(CLOSE_FAIL);
			if (cmd.redirs[i].type == OP_APPEND)
				cmd.fd_out = open_or_exit(cmd.redirs[i].arg, O_RDWR | O_CREAT | O_APPEND);
			else
				cmd.fd_out = open_or_exit(cmd.redirs[i].arg, O_RDWR | O_CREAT);
		}
		// TODO delimiter
		i++;
	}
}

int	execute(t_minishell *minishell)
{
	int	i;
	int	fd[2];
	int	j;

	i = 0;
	while (i < minishell->nb_cmds)
	{
		if (i + 1 < minishell->nb_cmds)
		{
			if (pipe(fd) == -1)
				error_and_exit(PIPE_FAIL); // TO THINK: does this make sense?
			minishell->cmd_table[i].fd_out = fd[1];
			minishell->cmd_table[i + 1].fd_in = fd[0];
		}
		execute_redirections(minishell->cmd_table[i]);
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
		// swap stdin/out with fd_in/out -> aftert the fork? we don't want to change stdout/in in main process...
		// fork and call execve -> how to get exit code from it? (check goncalo tuto)

		// error handling: if at some point something happens... still need to close stuff
		// and update exit code

		// close writing end of pipe and fd_out file if needed?
		// close fd[1] and close fd[0] from previous command! how? fd_in! if fd_in != 0
		// how to know if it's needed? has_pipe and has_redir booleans?
		if (minishell->cmd_table[i].fd_in != 0)
			close(minishell->cmd_table[i].fd_in);
		if (minishell->cmd_table[i].fd_out != 1)
			close(minishell->cmd_table[i].fd_out);
		i++;
	}
	return (minishell->exit_code);
}
