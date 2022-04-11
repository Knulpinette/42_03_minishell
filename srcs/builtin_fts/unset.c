#include "minishell.h"

/*
 * Error handling
 * Trying to unset a variable that doesn't exist is fine
 * But variable name needs to be valid as per export rules
 */

static int  invalid_identifier(char *arg)
{
    int i;

    if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (1);
	i = 1;
	while (arg[i])
    {
        if (!ft_isalnum(arg[i]) && arg[i] != '_')
            return (1);
		i++;
    }
	return (0);
}

int	unset(t_cmd_table *cmd, t_minishell *minishell)
{
    int		i;
    int		exit_code;

    i = 0;
    exit_code = 0;
    while (cmd->cmd_args[i])
    {
        if (invalid_identifier(cmd->cmd_args[i]))
        {
            error_message(INVALID_IDENTIFIER);
            exit_code = 1;
        }
        // check if var exists
        // if yes, remove it from list
        i++;
    }
    return (exit_code);
}