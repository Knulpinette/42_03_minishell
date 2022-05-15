#include "minishell.h"

/*
 * Given a specific element from ENV list
 */
char	*get_env_lst_name(t_list *env_lst)
{
	return (((t_env *)env_lst->content)->name);
}

char	*get_env_lst_value(t_list *env_lst)
{
	return (((t_env *)env_lst->content)->value);
}

/*
 * Using the whole ENV list (pointing at the beginning of it)
 */
t_list	*get_env_lst(char *name, t_list *env)
{
	t_minishell	*minishell;
	int			name_len;
	t_list		*to_get;

	if (!env)
	{
		minishell = get_minishell(NULL);
		to_get = minishell->env;
	}
	else
		to_get = env;
	name_len = ft_strlen(name);
	while (to_get && ft_strncmp(get_env_lst_name(to_get), name, name_len))
		to_get = to_get->next;
	return (to_get);
}

char	*get_env_value(char *name)
{
	t_list	*to_get;

	to_get = get_env_lst(name, NULL);
	if (!to_get)
		return (NULL);
	return (get_env_lst_value(to_get));
}

void	set_env_value(char *name, char *value)
{
	t_list	*to_set;

	to_set = get_env_lst(name, NULL);
	if (!to_set)
		return ;
	free(((t_env *)to_set->content)->value);
	((t_env *)to_set->content)->value = ft_strdup(value);
}
