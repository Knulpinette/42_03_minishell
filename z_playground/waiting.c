#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < 3)
	{
		pid = fork();
		if (pid == -1)
		{
			printf("Houston, we have a fork problem\n");
			return (1);
		}
		if (pid == 0)
		{
			printf("")
		}
		else
		{
			waitpid(pid, &status, 0); // synchronous, this is a problem
			if (WIFEXITED(status))
				minishell->exit_code = WEXITSTATUS(status);
			DEBUG(printf("Exit code: %d\n", WEXITSTATUS(status)));
		}
	}
}