#include "minishell.h"

void	print_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
}

void	print_tokens()
{
	return;
}
