#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

// /bin/ls
// /usr/bin/cd

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	pid_t	pid;
	char	*args[] = {"cd", "..", 0};

	pid = fork();
	if (pid == 0)
	{
		execve("/usr/bin/cd", args, envp);
		printf("There was an issue\n");
	}
}