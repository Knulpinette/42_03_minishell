#include "minishell.h"

/*
** 🦕🌴
**
**	set_signals
**
**	1. CTRL-C
**		Interrupt the current processes in minishell but NOT exit minishell.
**	2. CTRL-\
**		Do nothing. "Quit: 3\n"
**	3. CTRL-D (EOF)
**		Already works. Nothing to do.
**
**	The way our executor is build, we need to kill all ongoing processes
**	"manually".
**
** 🌴🥥
*/

static void	signal_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		//see if it would work with 
		//ft_putstr_fd(STDIN_FILENO, "^C\n"); 
		//instead and deleting ongoing processes
	}
	return ;
}

void	set_signals(pid_t *processes)
{
	int i;
	
	i = 0;
	if (processes)
	{
		while (processes[i])
		{
			kill(processes[i], SIGTERM);
			i++;
			DEBUG(write(STDIN_FILENO, "PROCESS\n", 14);)
		}
	}
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
