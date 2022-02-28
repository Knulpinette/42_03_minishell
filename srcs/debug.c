#include "minishell.h"

void	print_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
}

void	print_tokens(t_token *tokens, int words)
{
	int i;

	i = 0;
	while (i < words)
	{
		ft_putstr_fd(tokens[i].text, 2);
		ft_putstr_fd("\n", 2);
		i++;
	}
	return;
}
