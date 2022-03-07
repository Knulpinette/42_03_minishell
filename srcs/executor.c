#include "minishell.h"

int	execute(t_minishell *minishell)
{
	int	i;
	int	exit_code;

	i = 0;
	while (i < minishell->nb_cmd)
	{
		if (ft_strncmp(minishell->cmd_table[i].cmd_name, "cd", 2) == 0)
			exit_code = cd(&minishell->cmd_table[i]);
		if (ft_strncmp(minishell->cmd_table[i].cmd_name, "pwd", 3) == 0)
			exit_code = pwd(&minishell->cmd_table[i]);
		// not sure what to do with the exit code
		// need to return it in the end but... hmm...
		// should I do a child process even for built-in cmds?
		i++;
	}
	return (exit_code);
}
