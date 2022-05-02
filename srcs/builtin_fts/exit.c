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
	// 	convert int to unsigned char
	exit_code = minishell->exit_code;
	free_minishell(minishell);
	exit(exit_code);
	return (exit_code); //kinda stupid, but I need to return something...
}