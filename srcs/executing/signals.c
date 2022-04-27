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
		rl_replace_line("", 0); // you need to replace the line currently stored or else it will keep it in memory and display it again
		write(STDIN_FILENO, "\n", 1); // as per the subject
		rl_on_new_line(); // resetting rl for the new line you'll write
		rl_redisplay(); // display > (I think)
	}
	return ;
}

void	set_signals(void)
{
	// SO, minishell->child_pids will always be null, turns out. Doesn't seem to be a problem though. And looking at other people's code, it seems like no one is killing the processes... not sure of why it isn't working when I try stuff. Maybe I'm trying wrong because I'm not sure what's going on. 
	/*t_minishell	*minishell;
	int 		i;
	
	minishell = get_minishell(NULL);
	i = 0;
	if (minishell->child_pids)
	{
		DEBUG(write(STDIN_FILENO, "PROCESS\n", 14);)
		while (i < minishell->nb_cmds)
		{
			kill(minishell->child_pids[i], SIGTERM);
			i++;
		}
	}*/
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
