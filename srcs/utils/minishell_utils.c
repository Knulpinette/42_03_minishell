#include "minishell.h"

/*
** 🦕🌴
** 
**	get_minishell
**
**	This is a singleton. The concept is to create
**	an object once and then be able to access it
**	any time while not using global variable thanks
**	to a stored pointer.
**
** 🌴🥥
*/

t_minishell		*get_minishell(t_minishell *minishell)
{
	static t_minishell	*pointer_to_minishell = NULL;

	if (!pointer_to_minishell && minishell)
		pointer_to_minishell = minishell;
	return (pointer_to_minishell);
}

t_minishell		*init_minishell(char **envp, int argc)
{
	t_minishell *minishell;

	minishell = calloc_or_exit(sizeof(t_minishell), 1);
	get_minishell(minishell);
	if (argc != 2)
		minishell->mode = INTERACTIVE;
	else
		minishell->mode = NON_INTERACTIVE;
	minishell->nb_cmds = 0;
	minishell->instructions = NULL;
	minishell->env = init_env_lst(envp);
	minishell->env_paths = NULL;
	minishell->cmd_table = NULL;
	minishell->child_pids = NULL;
	minishell->exit_code = 0;
	return (minishell);
}

/*
**	Termcaps
**
**	ECHOCTL
**            (not in POSIX) If ECHO is also set, terminal special
**             characters other than TAB, NL, START, and STOP are echoed
**             as ^X, where X is the character with ASCII code 0x40
**             greater than the special character.  For example,
**             character 0x08 (BS) is echoed as ^H.
**	TCSANOW
**             the change occurs immediately.
*/

void	set_termcaps(void)
{
	struct termios	termcaps;

	tcgetattr(0, &termcaps);
	termcaps.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &termcaps);
}
