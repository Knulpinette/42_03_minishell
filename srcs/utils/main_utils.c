#include "minishell.h"

/* cool concept (singleton) taken from Michele who didn't use any global variables. 
 This allow us to store the pointer of minishell once and be able to
 reaccess it any point in our code, without passing the struct. 	*/
t_minishell		*get_minishell(t_minishell *minishell)
{
	static t_minishell	*pointer_to_minishell = NULL;

	if (!pointer_to_minishell && minishell)
		pointer_to_minishell = minishell;
	return (pointer_to_minishell);
}