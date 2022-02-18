#include "minishell.h"

void	free_minishell(t_minishell *minishell)
{
	printf("Theoretically, I freed minishell.\n");
	(void)minishell;
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
