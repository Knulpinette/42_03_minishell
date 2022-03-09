#include "minishell.h"

/*
 * 3 possible situations:
 * 1) no argument is given => change to HOME
 * 2) - => change to OLDPWD and print PWD
 * 3) relative or absolute path are given => change to path
 * chdir can receive both relative or absolute paths - so smart ✨
 *
 * Error Handling
 * In bash, additional arguments are ignored, if the first argument
 * is correct then the command works properly.
 * In zsh it says "cd: string not in pwd: <first_arg>"
 *
 * If we redirect the output from cd . (for e.g.) to a file (which is nothing)
 * it rewrites the file with nothing (if there was something there).
 * In order to obtain that effect, we write nothing (write(..., "", 0);)
 */

int	env_var_index(char *env_name)
{
	t_minishell	*minishell;
	int			env_name_len;
	int			i;

	minishell = get_minishell(NULL);
	env_name_len = ft_strlen(env_name);
	i = 0;
	while (minishell->envp[i] &&
		ft_strncmp(minishell->envp[i], env_name, env_name_len))
		i++;
	return (i);
}

char	*update_cwd(char *cwd)
{
	if (cwd)
		free(cwd);
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	return (cwd);
}

static char	*get_new_cwd(char *cmd_arg)
{
	if (!cmd_arg)
		return (getenv("HOME"));
	if (ft_strncmp(cmd_arg, "-", 1) == 0)
		return (getenv("OLDPWD"));
	return (cmd_arg);
}

int	cd(t_cmd_table *cmd, t_minishell *minishell)
{
	char		*cwd;
	char		*new_cwd;
	int			exit_code;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	new_cwd = get_new_cwd(cmd->cmd_args[0]);
	if ((exit_code = chdir(new_cwd)) != 0) 
	{
		free(cwd);
		error_message(WRONG_DIR);
		return (exit_code);
	}
	minishell->envp[env_var_index("OLDPWD")] = ft_strjoin("OLDPWD=", cwd); // free?
	cwd = update_cwd(cwd);
	minishell->envp[env_var_index("PWD")] = ft_strjoin("PWD=", cwd); // free?
	if (cmd->cmd_args[0] && ft_strncmp(cmd->cmd_args[0], "-", 1) == 0)
		pwd(cmd);
	else
		write(cmd->fd_in, "", 0); // test this once redirections are handled
	DEBUG(printf("PWD: %s\n", getenv("PWD")));
	DEBUG(printf("OLDPWD: %s\n", getenv("OLDPWD")));	
	free(cwd);
	return (0);
}
