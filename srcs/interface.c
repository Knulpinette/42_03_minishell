#include "minishell.h"

char	*get_instructions_line(t_mode mode, int fd)
{
	char	*line;
	int		ret;

	if (mode == INTERACTIVE)
	{
		line = readline(PROMPT);
		if (line && ft_strlen(line) > 0)
			add_history(line);
	}
	else
		ret = get_next_line(fd, &line);
	if (!line || (NON_INTERACTIVE && ret <= 0))
	{
		free(line);
		return (NULL);
	}
	return (line);
}