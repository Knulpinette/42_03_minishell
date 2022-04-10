#include "minishell.h"

/* Executing
 * 1. Creating a child process per command
 * 2. Figure out how to use multiple pipes
 * 3. Execve or run built-in command, accordingly
 */

int	main(int argc, char **argv, char **envp)
{
	int			fd;
	char		*line;
	t_minishell	*minishell;
	int			exit_code; // TODO think about this

	/* 1. assign signals to appropriate handlers
	 * 2. infinite while loop
	 *   a. get user input
	 *   b. parse it
	 *   c. execute it
	 */
	if (argc > 2)
		error_and_exit(WRONG_ARGC);
	fd = 0;
	if (argc == 2)
		fd = open_or_exit(argv[1], O_RDONLY);
	minishell = init_minishell(envp);
	while (1)
	{
		line = get_instructions_line(argc != 2, fd);
		if (!line)
			return (0);
		parse(line);
		free(line);
		exit_code = execute(minishell);
	}
	free_minishell(minishell);
	return (exit_code);
}
