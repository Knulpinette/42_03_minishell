#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Conclusions:
 * 1) I don't need envp as arg from main to be able to use getenv.
 *    Seems like there is an envp somewhere anyway...
 */


int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	int	i;

	i = 0;
	while (envp[i] && strncmp(envp[i], "PWD", 3))
		i++;
	envp[i] = strdup("PWD=heyo");
	printf("%s\n", getenv("PWD"));
	return (0);
}
