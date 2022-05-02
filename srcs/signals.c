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
**	Since signals react differently in the main/parent process nand in the child
**	process, we need to handle both case by resetting constantly the signals
**	according to where we are in the processes.
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

void	set_signals(t_status status, t_mode	mode)
{
	if (status == CHILD_PROCESS && mode == INTERACTIVE)
	{
		signal(SIGINT, signal_handler_child);
		signal(SIGQUIT, signal_handler_child);
	}
	else if (mode == INTERACTIVE)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}
