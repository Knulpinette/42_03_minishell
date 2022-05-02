#include "minishell.h"

int	str_only_digits(char *str)
{
	int	i;

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
	(void)cmd;
	(void)minishell;
	int	nb_args;

	nb_args = 0;
	while (cmd->cmd_args[nb_args])
		nb_args++;
	if (nb_args >= 1 !str_only_digits(cmd->cmd_args[0]))
	// if there's at least one argument and the first is not numeric
	// 	error and exit 255 - EXIT_ERROR
	// if too many arguments
	// 	error and return 1
	// if there is one argument
	// 	minishell exit code = that
	// 	convert int to unsigned char
	// exits cleaning up everything
	// return? shouldn't reach this return
	return (0);
}