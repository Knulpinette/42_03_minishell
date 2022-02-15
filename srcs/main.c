#include "minishell.h"

/* Global variable: env? history? both? none? */

/* Parsing
 * command struct:
 * - command
 * - flags (merged with command?)
 * - path (to be found after user input is all checked)
 * - built-in boolean ?
 * - fd_in (stdin if no redirection/infile is given)
 * - fd_out (stdout if no redirection/outfile is given)
 * - delimiter in case of <<
 * - mode (overwrite or append) in case of >>
 * - arguments -> array? what kind of arguments can we have?
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


int	main(void)
{
	/* 1. assign signals to appropriate handlers
	 * 2. infinite while loop
	 *   a. get user input
	 *   b. parse it
	 *   c. execute it
	 */
	return (0);
}
