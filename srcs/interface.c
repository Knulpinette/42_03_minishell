#include "minishell.h"

char	*get_instructions_line(int interactive, int fd)
{
	char	*line;

	if (interactive)
	{
		line = readline(PROMPT);
		if (line && ft_strlen(line) > 0)
			add_history(line);
	}
	else
		get_next_line(fd, &line);
	if (!line || (!interactive && !line[0]))
	{
		free(line);
		return (NULL);
	}
	return (line);
}
