#include "minishell.h"

void	free_minishell(t_minishell *minishell)
{
	int	i;
	int	nb_cmd;

	i = 0;
	nb_cmd = minishell->nb_cmd;
	if (minishell->cmd_table)
	{
		while (i < nb_cmd)
		{
			if (minishell->cmd_table[nb_cmd]->args)
				free_split(minishell->cmd_table[nb_cmd]->args);
			i++;
			printf("%i\n", i);
		}
		free(minishell->cmd_table);
	}
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
