#include "minishell.h"

/*
 * 🥥🌴 EXECUTOR - Step by step 🥥🌴
 *
 * 1. PIPES
 *	If there's a next command, open the pipe
 *	Update fd_out from current command and fd_in from next command
 *
 * 2. REDIRECTIONS -> in exec_redirs.c
 *	Closes previous fd_in/out if not stdin/out (so pipe and other redirection)
 *	Opens the new one
 *	If something happens we're out with exit_code 1
 *
 * 3. NO CMD
 *	If there's no command, we're out with exit_code 0
 *
 * 4. BUILT-IN FUNCTION -> in exec_cmd.c
 *	If the function is built-in, call it and update exit_code
 *	If it's not built-in, returns 0 and calls function to execute other commands
 *
 * 5. SYSTEM FUNCTION / NON-BUILT-IN -> in exec_cmd.c
 * WIFEXITED(status) returns 1 if child terminated normally
 * WEXITSTATUS(status) returns child's exit code
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
	int		i;
	int		fd[2];
	pid_t	pid;
	int		status;

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
		if (is_builtin(minishell->cmd_table[i].cmd_name) && minishell->nb_cmds == 1)
			minishell->exit_code = exec_builtin(minishell, &minishell->cmd_table[i]);
		else
		{
			pid = fork();
			if (pid == -1)
				error_and_exit(FORK_FAIL);
			if (pid == 0)
			{
				if (is_builtin(minishell->cmd_table[i].cmd_name))
					exit(exec_builtin(minishell, &minishell->cmd_table[i]));
				exec_system(minishell, &minishell->cmd_table[i]);
			}
			else
			{
				waitpid(pid, &status, 0); // synchronous, this is a problem
				if (WIFEXITED(status))
					minishell->exit_code = WEXITSTATUS(status);
				DEBUG(printf("Exit code: %d\n", WEXITSTATUS(status)));
			}
		}
		// have an array of exit_codes
		close_for_next_cmd(minishell->cmd_table[i]);
		i++;
	}
	// update exit_code with last one
	return (minishell->exit_code);
}
