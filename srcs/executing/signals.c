#include "minishell.h"

static void	signal_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

void	set_signals(pid_t *child_processes)
{
	int i;
	
	i = 0;
	if (child_processes)
	{
		while (child_processes[i])
		{
			kill(child_processes[i], SIGTERM);
			i++;
		}
	}
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
