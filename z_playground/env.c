#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/*
 * Conclusions:
 * 1) I don't need envp as arg from main to be able to use getenv not setenv.
 *    Seems like there is an envp somewhere anyway...
 * 2) Neither this misterious env nor the envp argument change automatically
 *    when they should (for example, when chdir function is used)
 * 3) If we always need to set it up manually, then we might as well create our
 *    own structure for it...
 */


int	main(void)
{
	int	i;

	i = 0;
	//while (envp[i] && strncmp(envp[i], "PWD", 3))
	//	i++;
	//envp[i] = strdup("PWD=heyo");
	chdir("/Users/svieira/");
	printf("%s\n", getenv("PWD"));
	return (0);
}
