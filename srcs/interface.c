#include "minishell.h"

char	*get_instructions_line(t_mode mode, int fd)
{
	char	*line;
	int		nb_bits_read;

	if (mode == INTERACTIVE)
	{
		line = readline(PROMPT);
		if (line && ft_strlen(line) > 0)
			add_history(line);
	}
	else
		nb_bits_read = get_next_line(fd, &line);
	DEBUG(printf("nb_bits_read = %i\n", nb_bits_read);)
	if (!line || (mode == NON_INTERACTIVE && nb_bits_read <= 0))
	{
		free(line);
		return (NULL);
	}
	return (line);
}
