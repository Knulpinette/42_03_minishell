#include "minishell.h"

/*
 * Error handling
 * Export without options - thus it will ignore any flags and not throw out an error
 * Starts with digit or with = : bash: export: `1test': not a valid identifier
 * Has a symbol (/ % * + , - . : ? [] {} ^ ~): bash: export: `/test': not a valid identifier
 * Some symbols are ignored or lead to special behaviour (# & $ ! ; and parsing stuff)
 * Some symbols are accepted (_)
 *
 * Each argument leads to a new variable
 * The variable only has a value if there's an =
 * If one prompts an error, the next one is still added
 */

void	print_export(t_list *env, int fd_in)
{
	while (env)
	{
		ft_putstr_fd("declare -x ", fd_in);
		ft_putstr_fd(get_env_lst_name(env), fd_in);
		if (get_env_lst_value(env)) // it's printing when it shouldn't
		{
			write(fd_in, "=\"", 2);
			ft_putstr_fd(get_env_lst_value(env), fd_in);
			write(fd_in, "\"", 1);
		}
		write(fd_in, "\n", 1);
		env = env->next;
	}
}

int	add_env_list(char *arg, t_list *env)
{
	int		i;
	t_env	*env_var;
	//check input and give errors
	//redo env_content with proper error/exit handling
	//env_var = new_env_content(envp[i]); // what happens when null
	
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (1);
	i = 1;
	while (arg[i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
		i++;
	if (arg[i] && arg[i] != '=')
		return (1);
	env_var = (t_env *)malloc(sizeof(t_env));
	env_var->name = ft_substr(arg, 0, i);
	if (arg + i)
		env_var->value = ft_strdup(arg + i + 1);
	else
		env_var->value = NULL;
	ft_lstadd_back(&env, ft_lstnew((void *)env_var));
	return (0);
}

int	export(t_cmd_table *cmd, t_minishell *minishell)
{
	t_list	*sorted_env;
	int		i;
	int		exit_code;

	if (!cmd->cmd_args[0])
	{
		sorted_env = copy_env_lst(minishell->env);
		merge_sort(&sorted_env);
		print_export(sorted_env, cmd->fd_in);
		// understand difference between assigned and unassigned env vars
		ft_lstclear(&sorted_env, &del_env_content);
		return (0);
	}
	// add the new var to the list - this is actually simpler
	i = 0;
	while (cmd->cmd_args[i])
	{
		exit_code = add_env_list(cmd->cmd_args[i], minishell->env);
		if (exit_code)
			error_message(INVALID_IDENTIFIER);
		i++;
	}
	// check if there's a limit to nb of arguments it can handle
	// error handling with wrong args
	return (exit_code);
}
