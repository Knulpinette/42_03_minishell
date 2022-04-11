#include "minishell.h"

t_env	*new_env_content(char *var)
{
	int		i;
	t_env	*env_var;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	env_var = (t_env *)malloc(sizeof(t_env));
	env_var->name = ft_substr(var, 0, i);
	if (var + i)
		env_var->value = ft_strdup(var + i + 1);
	else
		env_var->value = NULL;
	return (env_var);
}

t_list	*init_env_lst(char **envp)
{
	int		i;
	t_env	*env_var;
	t_list	*env_lst;

	i = 0;
	env_lst = NULL;
	while (envp[i])
	{
		env_var = new_env_content(envp[i]);
		ft_lstadd_back(&env_lst, ft_lstnew((void *)env_var));
		i++;
	}
	return (env_lst);
}

t_list	*copy_env_lst(t_list *original)
{
	t_env	*env_var;
	t_list	*copy;

	copy = NULL;
	while (original)
	{
		env_var = (t_env *)malloc(sizeof(t_env));
		env_var->name = ft_strdup(get_env_lst_name(original));
		env_var->value = ft_strdup(get_env_lst_value(original));
		ft_lstadd_back(&copy, ft_lstnew((void *)env_var));
		original = original->next;
	}
	return (copy);
}

void	del_env_content(void *env_var)
{
	free(((t_env *)env_var)->name);
	free(((t_env *)env_var)->value);
}
