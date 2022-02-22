#include "minishell.h"

/* Parsing
 * 1. Understand how many commands are in one line; Since we don't have to handle ;
 *    nor && nor || I think the only possible delimiter is a pipe
 * 2. Treat each command: find the path; expand variables ($); handle quotes; open infile
 *    and/or outfile if applicable
 * 3. Add the struct to the linked list?
 */

/* Executing
 * 1. Creating a child process per command
 * 2. Figure out how to use multiple pipes
 * 3. Execve or run built-in command, accordingly
 */

int	main(int argc, char **argv)
{
	int			fd;
	char		*line;
	t_minishell	*minishell;
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
	minishell = init_minishell();
	while (1)
	{
		line = get_instructions_line(argc != 2, fd);
		if (!line)
			return (0);
		// validate user input (line)
		parse(line);
		// if not valid, free line and return 1
		// parse(line) and turn it into a linked list of command structs
		free(line);
		// executor
	}
	free_minishell(minishell);
	return (EXIT_SUCCESS);
}
