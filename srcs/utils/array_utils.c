#include "minishell.h"

/*
** get_array_len
**
** Gets the length of a null-terminated array.
*/

int	get_array_len(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}
