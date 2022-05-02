#include "minishell.h"

int	str_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
 * Note: I know it's silly to return after exit
 * but I kinda had to return something...
 * better something that kinda makes sense
 */
int	exit_cocoshell(t_cmd_table *cmd, t_minishell *minishell)
{
	int	nb_args;
	int	exit_code;

	nb_args = 0;
	while (cmd->cmd_args[nb_args])
		nb_args++;
	ft_putstr_fd("exit\n", cmd->fd_out); // doesn't show when in pipes
	if (nb_args >= 1 && !str_only_digits(cmd->cmd_args[0]))
		error_and_exit(NON_NUM_ARG);
	if (nb_args > 1)
		return (error_and_return(TOO_MANY_ARGS, 1));
	if (nb_args == 1)
		minishell->exit_code = ft_atoi(cmd->cmd_args[0]);
	exit_code = minishell->exit_code;
	free_minishell(minishell);
	exit(exit_code);
	return (exit_code);
}