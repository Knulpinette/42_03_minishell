#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../42_00_libft/libft.h"

/*
 * Conclusions:
 * 1) I don't need envp as arg from main to be able to use getenv nor setenv.
 *    Seems like there is an envp somewhere anyway...
 * 2) Neither this misterious env nor the envp argument change automatically
 *    when they should (for example, when chdir function is used)
 * 3) If we modify envp arg manually, getenv will retrieve the updated value
 * 4) If we create something else out of envp and update it, it won't
 */

typedef struct s_env {
	char			*name;
	char			*value;
}				t_env;

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

void	free_env_lst(t_list **env_lst)
{
	ft_lstclear(env_lst, &del_env_content);
}

char	*get_env_name(t_list *env_lst)
{
	return (((t_env *)env_lst->content)->name);
}

t_list	*get_env_lst(t_list *env_lst, char *name)
{
	int		name_len;
	t_list	*to_get;

	name_len = ft_strlen(name);
	to_get = env_lst;
	while (to_get && ft_strncmp(get_env_name(to_get), name, name_len))
		to_get = to_get->next;
	return (to_get);
}

void	set_env_value(t_list *env_lst, char *name, char *value)
{
	t_list	*to_set;

	to_set = get_env_lst(env_lst, name);
	free(((t_env *)to_set->content)->value);
	((t_env *)to_set->content)->value = ft_strdup(value);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_list	*env_lst;
	t_list	*to_change;

	env_lst = init_env_lst(envp);
	/*printf("%s=", ((t_env *)env_lst->content)->name);
	printf("%s\n", ((t_env *)env_lst->content)->value);
	printf("%s=", ((t_env *)env_lst->next->content)->name);
	printf("%s\n", ((t_env *)env_lst->next->content)->value);*/
	to_change = get_env_lst(env_lst, "PWD");
	printf("%s=", get_env_name(to_change)); 
	set_env_value(env_lst, "PWD", "/Users/svieira/");
	printf("%s\n", ((t_env *)to_change->content)->value);
	//setenv("PWD", "/Users/svieira/", 1);
	//printf("%s\n", getenv("PWD"));
	free_env_lst(&env_lst);
	return (0);
}
