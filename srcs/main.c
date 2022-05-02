#include "minishell.h"

/*
	ECHOCTL
              (not in POSIX) If ECHO is also set, terminal special
              characters other than TAB, NL, START, and STOP are echoed
              as ^X, where X is the character with ASCII code 0x40
              greater than the special character.  For example,
              character 0x08 (BS) is echoed as ^H.  [requires
              _BSD_SOURCE or _SVID_SOURCE]
	TCSANOW
              the change occurs immediately.
*/

void	set_termcaps(void)
{
	struct termios	termcaps;

	tcgetattr(0, &termcaps);
	termcaps.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &termcaps);
}

int	main(int argc, char **argv, char **envp)
{
	int					fd;
	char				*line;
	t_minishell			*minishell;
	int					exit_code;
	
	set_termcaps();
	if (argc > 2)
		error_and_exit(WRONG_ARGC);
	fd = 0;
	if (argc == 2)
		fd = open_or_exit(argv[1], O_RDONLY);
	minishell = init_minishell(envp, argc);
	set_signals(INIT, minishell->mode);
	while (1)
	{
		line = get_instructions_line(minishell->mode, fd);
		if (!line)
			break ;
		exit_code = parse(line);
		free(line);
		if (exit_code != SYNTAX_ERROR && minishell->nb_cmds)
			exit_code = execute(minishell);
	}
	free_minishell(minishell);
	return (exit_code);
}
