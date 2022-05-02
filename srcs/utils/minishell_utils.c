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
** (Text is extracted from @gleal very precious README on this project
**	and the termcaps documentation)
**
**	Termcaps stands for terminal capabilities.
**
**		struct termios {
**			tcflag_t c_iflag;
**			tcflag_t c_oflag;
**			tcflag_t c_cflag;
**			tcflag_t c_lflag;
**			cc_t c_cc[NCCS];
**			speed_t c_ispeed;
**			speed_t c_ospeed;
**		};
**
**			1.	int tcgetattr(int fd, struct termios *termios_p);
**		we check if there is a terminfo database
**		(database with all terminal capabilities) for the TERM environment
**		variable in our envp array and load the functions internally, so that
**		the tgetstr function works.
**
**			2.	int tcsetattr(int fd, int optional_actions,
**					   			 const struct termios *termios_p);
**		to check and save in a struct and tputs to activate the 
**		following capabilities:
**
**		ECHOCTL
**            (not in POSIX) If ECHO is also set, terminal special
**             characters other than TAB, NL, START, and STOP are echoed
**             as ^X, where X is the character with ASCII code 0x40
**             greater than the special character.  For example,
**             character 0x08 (BS) is echoed as ^H.
** 			~ECHOCTL : Turns off the standard echo of "CTRL + KEY"
**		TCSANOW
**             the change occurs immediately.
**
*/

void	set_termcaps(void)
{
	struct termios	termcaps;

	tcgetattr(0, &termcaps);
	termcaps.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &termcaps);
}
