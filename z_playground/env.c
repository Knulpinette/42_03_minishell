#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../42_00_libft/libft.h"

/*
 * Conclusions:
 * 1) I don't need envp as arg from main to be able to use getenv not setenv.
 *    Seems like there is an envp somewhere anyway...
 * 2) Neither this misterious env nor the envp argument change automatically
 *    when they should (for example, when chdir function is used)
 * 3) If we always need to set it up manually, then we might as well create our
 *    own structure for it...
 */

typedef struct s_env {
	char			*name;
	char			*value;
}				t_env;

t_env	new_env_content(char *var)
{
	int		i;
	t_env	env_var;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	env_var.name = ft_substr(var, 0, i);
	env_var.value = ft_strdup(getenv(env_var.name));
	return (env_var);
}

t_list	*init_env(char **envp)
{
	int		i;
	t_env	env_var;
	t_list	*env_lst;

	i = 0;
	env_lst = NULL;
	while (envp[i])
	{
		env_var = new_env_content(envp[i]);
		// should I allocate memory to env_var or the list?
		// wondering because in the list it's type void
		ft_lstadd_back(&env_lst, ft_lstnew((void *)&env_var));
		printf("new item added\n");
		i++;
	}
	return (env_lst);
}

void	del_env_content(void *env_var)
{
	free(((t_env *)env_var)->name);
	free(((t_env *)env_var)->value);
	printf("deleted content\n");
}

void	free_env(t_list **env)
{
	ft_lstclear(env, &del_env_content);
	printf("deleted list\n");
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	int		i;
	t_list	*env;

	i = 0;
	env = init_env(envp);
	//	i++;
	//envp[i] = strdup("PWD=heyo");
	setenv("PWD", "/Users/svieira/", 1);
	printf("%s\n", getenv("PWD"));
	free_env(&env);
	return (0);
}
