#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define NB_KIDS 3

int	main(void)
{
	int		i;
	pid_t	pid[NB_KIDS];
	int		status;
	int		exit_code[NB_KIDS];
	int		j;

	i = 0;
	while (i < NB_KIDS)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			printf("Houston, we have a problem\n");
			return (1);
		}
		if (pid[i] == 0)
		{
			sleep(NB_KIDS - i);
			printf("Child process %d\n", i);
			exit(i);
		}
		else if (i == NB_KIDS - 1)
		{
			j = 0;
			while (j < NB_KIDS)
			{
				waitpid(pid[j], &status, 0);
				if (WIFEXITED(status))
					exit_code[j] = WEXITSTATUS(status);
				j++;
			}
		}
		i++;
	}
	i = 0;
	while (i < NB_KIDS)
	{
		printf("Exit code: %d\n", exit_code[i]);
		i++;
	}
	return (exit_code[NB_KIDS - 1]);
}