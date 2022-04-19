#include "minishell.h"

/*
 * What are errors?
 * Since echo treats wrong flags as a text argument,
 * there's nothing that could go wrong...
 * unless something goes wrong with write => returns -1
 * ALERT: Right now we don't catch an error if something goes wrong
 * inside ft_putstr_fd (since it returns void... who thought of that? 42...)
 */

static int  exit_echo(void)
{
    error_message(WRITE_FAIL);
    return (-1);
}

int	echo(t_cmd_table *cmd)
{
    int i;
    int bytes_written;

    i = 0;
    while (cmd->cmd_args[i])
    {
        ft_putstr_fd(cmd->cmd_args[i], cmd->fd_out);
        bytes_written = write(cmd->fd_out, " ", 1);
        if (bytes_written == -1)
            return (exit_echo());
        i++;
    }
    if (!(cmd->flags[0] && cmd->flags[0][1] == 'n'))
        bytes_written = write(cmd->fd_out, "\n", 1);
    if (bytes_written == -1)
        return (exit_echo());
    return (0);
}