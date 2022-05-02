#include "minishell.h"

/*
** 🦕🌴
**
**	set_signals
**
**	1. CTRL-C
**		Interrupt the current processes in minishell but NOT exit minishell.
**		(in process, just newline)
**	2. CTRL-\
**		Do nothing. (in process) "Quit: 3\n"
**	3. CTRL-D (EOF)
**		Already works. Nothing to do.
**
**	The way our executor is build, we need to kill all ongoing processes
**	"manually".
**
** 🌴🥥
*/

static void	sigint_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		rl_replace_line("", 0);
		write(STDIN_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

static void	signal_handler_child(int sig_num)
{
	if (sig_num == SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
	if (sig_num == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
	return ;
}

void	set_signals(t_status status)
{
	if (status == CHILD_PROCESS)
	{
		DEBUG(printf("current_signal = %d\n", status);)
		signal(SIGINT, signal_handler_child);
		signal(SIGQUIT, signal_handler_child);
	}
	else
	{
		DEBUG(printf("current_signal = %d\n", status);)
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}
