#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int					fd;
	char				*line;
	t_minishell			*minishell;
	int					exit_code;

	if (argc > 2)
		error_and_exit(WRONG_ARGC);
	fd = 0;
	if (argc == 2)
		fd = open_or_exit(argv[1], O_RDONLY);
	minishell = init_minishell(envp);
	set_signals();
	while (1)
	{
		line = get_instructions_line(argc != 2, fd);
		if (!line)
			return (0); // shouldn't this be break? o.O what was I thinking?
		exit_code = parse(line);
		free(line);
		if (exit_code != SYNTAX_ERROR)
			exit_code = execute(minishell);
	}
	free_minishell(minishell);
	return (exit_code);
}
