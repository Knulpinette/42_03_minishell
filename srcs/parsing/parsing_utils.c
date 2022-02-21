#include "minishell.h"

char	*skip_space(t_minishell *minishell)
{
	while ((*minishell->prompt) && (*minishell->prompt) == SPACE)
		minishell++; //faire la fonction
	return (minishell->prompt);
}