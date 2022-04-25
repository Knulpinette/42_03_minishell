#include "minishell.h"

/*
** Checks if the command exists on each path and is executable
** Access function: F_OK - command exists
**                  X_OK - is executable
** If yes, the path is stored in that cmd_table, ready to be used
*/
int	valid_command(t_minishell *minishell, t_cmd_table *cmd)
{
	int	i;

	i = 0;
	while (minishell->env_paths[i])
	{
		if (cmd->cmd_path)
			free(cmd->cmd_path);
		cmd->cmd_path = ft_strjoin(minishell->env_paths[i], cmd->cmd_name);
		if (access(cmd->cmd_path, F_OK) == 0
			&& access(cmd->cmd_path, X_OK) == 0)
			return (1);
		i++;
	}
	return (0);
}

static char **build_execve_args(t_cmd_table *cmd)
{
    char    **execve_args;
    int     i;

    execve_args = (char **)calloc_or_exit(sizeof(char *), cmd->nb_tokens + 1);
    i = 0;
    while (i < cmd->nb_tokens)
    {
        execve_args[i] = ft_strdup(cmd->tokens[i].text);
        i++;
    }
     execve_args[i] = NULL;
     return (execve_args);
}

static char **build_execve_envp(t_minishell *minishell)
{
    char    **envp;
    int     i;
    t_list  *curr;
    int     len_name;
    int     len_value;

    envp = (char **)calloc_or_exit(sizeof(char *), ft_lstsize(minishell->env) + 1);
    i = 0;
    curr = minishell->env;
    while (curr)
    {
        len_name = ft_strlen(get_env_lst_name(curr));
        len_value = 0;
        if (get_env_lst_value(curr))
            len_value = ft_strlen(get_env_lst_value(curr));
        envp[i] = (char *)calloc_or_exit(sizeof(char), len_name + len_value + 2);
        ft_strlcpy(envp[i], get_env_lst_name(curr), len_name + 1);
        envp[i][len_name] = '=';
        if (len_value != 0)
            ft_strlcat(envp[i], get_env_lst_value(curr),
                len_name + len_value + 2);
        curr = curr->next;
        i++;
    }
     envp[i] = NULL;
     return (envp);
}

// fork and call execve -> how to get exit code from it? (check goncalo tuto)
void exec_system(t_minishell *minishell, t_cmd_table *cmd)
{
    char    **execve_args;
    char    **envp;

    if (cmd->fd_in != 0)
    {
    	dup2(cmd->fd_in, STDIN_FILENO);
    	close(cmd->fd_in);
    }
    if (cmd->fd_out != 1)
    {
    	dup2(cmd->fd_out, STDOUT_FILENO);
    	close(cmd->fd_out);
    }
    get_cmd_paths(minishell);
    if (valid_command(minishell, cmd))
    {
        execve_args = build_execve_args(cmd);
        /*DEBUG(printf("EXECVE ARGS:\n"));
        DEBUG(print_split(execve_args));
        DEBUG(printf("\n\n"));*/
        envp = build_execve_envp(minishell);
        execve(cmd->cmd_path, execve_args, envp);
        DEBUG(printf("execve failed\n"));
        free_split(execve_args);
        free(envp);
    }
    // get exit code from execve
    // cmd not found -> exit code 127
    error_and_exit(WRONG_CMD);
}
