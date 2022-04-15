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

static void	print_export(t_list *env, int fd_in)
{
	while (env)
	{
		ft_putstr_fd("declare -x ", fd_in);
		ft_putstr_fd(get_env_lst_name(env), fd_in);
		if (get_env_lst_value(env))
		{
			write(fd_in, "=\"", 2);
			ft_putstr_fd(get_env_lst_value(env), fd_in);
			write(fd_in, "\"", 1);
		}
		write(fd_in, "\n", 1);
		env = env->next;
	}
}

static int	add_env_list(char *arg, t_list *env)
{
	int		i;
	t_env	*env_var;
	
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (1);
	i = 1;
	while (arg[i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
		i++;
	if (arg[i] && arg[i] != '=')
		return (1);
	env_var = (t_env *)calloc_or_exit(sizeof(t_env), 1);
	env_var->name = ft_substr(arg, 0, i);
	if (arg[i])
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
		ft_lstclear(&sorted_env, &del_env_content);
		return (0);
	}
	i = 0;
	exit_code = 0;
	while (cmd->cmd_args[i])
	{
		if (add_env_list(cmd->cmd_args[i], minishell->env))
		{
			error_message(INVALID_IDENTIFIER);
			exit_code = 1;
		}
		i++;
	}
	return (exit_code);
}
