#include "minishell.h"

int	open_quotes(char *line)
{
	int	single_quotes;
	int	double_quotes;
	int	i;

	single_quotes = 0;
	double_quotes = 0;
	i = 0;
	while (line[i])
	{
		if (!single_quotes && line[i] == '"')
			double_quotes = !double_quotes;
		if (!double_quotes && line[i] == '\'')
			single_quotes = !single_quotes;
		i++;
	}
	if (single_quotes || double_quotes)
		return (1);
	return (0);
}

char	*get_instructions_line(int interactive, int fd)
{
	char	*line;
	char	*next_line;
	char	*tmp_line;

	if (interactive)
		line = readline(PROMPT);
	else
		get_next_line(fd, &line);
	if (!line || (!interactive && !line[0]))
	{
		free(line);
		return (NULL);
	}
	while (open_quotes(line))
	{
		if (interactive)
			next_line = readline(PROMPT);
		else
			get_next_line(fd, &next_line);
		tmp_line = ft_strjoin(line, next_line);
		free(line);
		line = tmp_line;
		free(next_line);
	}
	return (line);
}
