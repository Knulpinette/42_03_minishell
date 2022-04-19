#include "minishell.h"

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

int	exec_redirs(t_cmd_table *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->nb_redirs)
	{
		if (cmd->redirs[i].type == OP_REDIR_IN)
		{
			if (cmd->fd_in != 0 && close(cmd->fd_in) == -1)
				error_and_exit(CLOSE_FAIL);
			if ((cmd->fd_in = open(cmd->redirs[i].arg, O_RDWR, 00755)) == -1)
				return (error_and_return(OPEN_FAIL, 1));
		}
		else if (cmd->redirs[i].type == OP_REDIR_OUT || cmd->redirs[i].type == OP_APPEND)
		{
			if (exec_redirs_out(cmd, i))
                return (1);
		}
		// TODO delimiter
		i++;
	}
	DEBUG(printf("Redir In: %d, Redir Out: %d\n", cmd->fd_in, cmd->fd_out));
	return (0);
}