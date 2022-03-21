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
 * In bash, the first time we open the terminal there is no OLDPWD yet,
 * thus calling cd - returns "bash: cd: OLDPWD not set"
 *
 * If we redirect the output from cd . (for e.g.) to a file (which is nothing)
 * it rewrites the file with nothing (if there was something there).
 * In order to obtain that effect, we write nothing (write(..., "", 0);)
 */

char	*update_cwd(char *cwd)
{
	if (cwd)
		free(cwd);
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	return (cwd);
}

static char	*get_new_cwd(t_list *env, char *cmd_arg)
{
	if (!cmd_arg)
		return (get_env_value(env, "HOME"));
	if (ft_strncmp(cmd_arg, "-", 1) == 0)
		return (get_env_value(env, "OLDPWD"));
	return (cmd_arg);
}

static int	exit_cd(char *cwd, int	error_code, int exit_code)
{
	free(cwd);
	error_message(error_code);
	return (exit_code);
}

int	cd(t_cmd_table *cmd, t_minishell *minishell)
{
	char		*cwd;
	char		*new_cwd;
	int			exit_code;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if ((new_cwd = get_new_cwd(minishell->env, cmd->cmd_args[0])) == NULL)
		return (exit_cd(cwd, NO_OLDPWD, 1));
	if ((exit_code = chdir(new_cwd)) != 0) 
		return (exit_cd(cwd, WRONG_DIR, exit_code));
	set_env_value(minishell->env, "OLDPWD", cwd);
	cwd = update_cwd(cwd);
	set_env_value(minishell->env, "PWD", cwd);
	if (cmd->cmd_args[0] && ft_strncmp(cmd->cmd_args[0], "-", 1) == 0)
		pwd(cmd);
	else
		write(cmd->fd_in, "", 0); // test this once redirections are handled
	DEBUG(printf("PWD: %s\n", get_env_value(minishell->env, "PWD")));
	DEBUG(printf("OLDPWD: %s\n", get_env_value(minishell->env, "OLDPWD")));	
	free(cwd);
	return (0);
}
