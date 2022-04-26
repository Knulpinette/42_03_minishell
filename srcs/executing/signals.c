#include "minishell.h"

static void	signal_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		//see if it would work with ft_putstr_fd(STDIN_FILENO, "^C\n"); instead and deleting ongoing processes
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
			DEBUG(write(STDIN_FILENO, "CHILD_PROCESS\n", 14);)
		}
	}
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
