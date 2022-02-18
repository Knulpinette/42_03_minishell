#include "minishell.h"

int	main(void)
{
	t_minishell	minishell;
	t_minishell *test;

	minishell.coconut = "cocoshells";
	test = get_minishell(&minishell);
	printf("%s\n", test->coconut);
	error_and_exit(MEMORY_FAIL);
	return (0);
}
