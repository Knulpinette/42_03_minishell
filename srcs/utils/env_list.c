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
	env_var->value = ft_strdup(getenv(env_var->name));
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

void	del_env_content(void *env_var)
{
	free(((t_env *)env_var)->name);
	free(((t_env *)env_var)->value);
}