#include "minishell.h"

void	free_minishell(t_minishell *minishell)
{
	if (minishell->cmd_table[0].args)
		free_split(minishell->cmd_table[0].args);
	if (minishell->cmd_table)
		free(minishell->cmd_table);
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
