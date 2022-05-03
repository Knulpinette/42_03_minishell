#include "minishell.h"

static int	exec_redirs_in(t_cmd_table *cmd, int i)
{
	//char	*line;

	if (cmd->fd_in != 0 && close(cmd->fd_in) == -1)
		error_and_exit(CLOSE_FAIL);
	if (cmd->redirs[i].type == OP_REDIR_IN)
		cmd->fd_in = open(cmd->redirs[i].arg, O_RDWR, 00755);
	/*else
	{
		cmd->fd_in = open("temp", O_RDWR | O_TMPFILE | O_APPEND, 00755);
		// do heredocs thingy
		// call readline
		// write result into file temp
		// when do I close the file? close and remove it!
	}*/
	if (cmd->fd_in == -1)
		return (error_and_return(OPEN_FAIL, 1));
	return (0);
}

static int  exec_redirs_out(t_cmd_table *cmd, int i)
{
	if (cmd->fd_out != 1 && close(cmd->fd_out) == -1)
		error_and_exit(CLOSE_FAIL);
	if (cmd->redirs[i].type == OP_APPEND)
		cmd->fd_out = open(cmd->redirs[i].arg, O_RDWR | O_CREAT | O_APPEND, 00755);
	else
	{
		cmd->fd_out = open(cmd->redirs[i].arg, O_RDWR | O_CREAT | O_TRUNC, 00755);
	}
	if (cmd->fd_out == -1)
		return (error_and_return(OPEN_FAIL, 1));
	return (0);
}

int	exec_redirs(t_minishell *minishell, t_cmd_table *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->nb_redirs)
	{
		if (cmd->redirs[i].type == OP_REDIR_IN
			|| cmd->redirs[i].type == OP_DELIMITER)
		{
			if (exec_redirs_in(cmd, i))
			{
				minishell->exit_code = 1;
				return (1);
			}
		}
		else if (cmd->redirs[i].type == OP_REDIR_OUT
			|| cmd->redirs[i].type == OP_APPEND)
		{
			if (exec_redirs_out(cmd, i))
			{
				minishell->exit_code = 1;
				return (1);
			}
		}
		i++;
	}
	DEBUG(printf("Redir In: %d, Redir Out: %d\n", cmd->fd_in, cmd->fd_out));
	return (0);
}