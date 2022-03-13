#include "minishell.h"

int		get_array_len(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}
