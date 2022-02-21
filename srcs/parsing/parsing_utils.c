#include "minishell.h"

char	*skip_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == SPACE)
		i++;; //faire la fonction
	return (line + i);
}