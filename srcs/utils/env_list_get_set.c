#include "minishell.h"

char	*get_env_lst_name(t_list *env_lst)
{
	return (((t_env *)env_lst->content)->name);
}

char	*get_env_lst_value(t_list *env_lst)
{
	return (((t_env *)env_lst->content)->value);
}

t_list	*get_env_lst(t_list *env_lst, char *name)
{
	int		name_len;
	t_list	*to_get;

	name_len = ft_strlen(name);
	to_get = env_lst;
	while (to_get && ft_strncmp(get_env_lst_name(to_get), name, name_len))
		to_get = to_get->next;
	return (to_get);
}

char	*get_env_value(t_list *env_lst, char *name)
{
	t_list	*to_get;

	to_get = get_env_lst(env_lst, name);
	return (get_env_lst_value(to_get));
}

void	set_env_value(t_list *env_lst, char *name, char *value)
{
	t_list	*to_set;

	to_set = get_env_lst(env_lst, name);
	free(((t_env *)to_set->content)->value);
	((t_env *)to_set->content)->value = ft_strdup(value);
}
