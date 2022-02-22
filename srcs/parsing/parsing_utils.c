#include "minishell.h"

char	*skip_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == SPACE)
		i++;; //faire la fonction
	return (line + i);
}

int		get_split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

t_token	*new_token(void *token)
{
	t_list	*list;

	list = (t_token *)malloc(sizeof(t_token));
	if (!list)
		return (NULL);
	list->type = NULL;
	list->token = token;
	list->next = 0;
	return (list);
}
