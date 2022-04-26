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

static void	child_signal_handler(int sig_num)
{
	if (sig_num == SIGINT)
		write(1, "\n", 3);
	else if (sig_num == SIGQUIT)
		write(1, "Quit: 3\n", 8);
	else
		return ;
}

void	signals(t_process process)
{
	if (process == CHILD_PROCESS)
	{
		signal(SIGINT, child_signal_handler);
		signal(SIGQUIT, child_signal_handler);
	}
	else
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}
