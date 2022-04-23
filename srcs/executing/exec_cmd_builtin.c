#include "minishell.h"

int is_builtin(char *cmd_name)
{
    if (ft_strncmp(cmd_name, "cd", 2) == 0
        || ft_strncmp(cmd_name, "pwd", 3) == 0
        || ft_strncmp(cmd_name, "env", 3) == 0
        || ft_strncmp(cmd_name, "echo", 4) == 0
        || ft_strncmp(cmd_name, "export", 6) == 0
        || ft_strncmp(cmd_name, "unset", 5) == 0
        || ft_strncmp(cmd_name, "exit", 4) == 0)
        return (1);
    return (0);
}

int exec_builtin(t_minishell *minishell, t_cmd_table *cmd)
{
    if (ft_strncmp(cmd->cmd_name, "cd", 2) == 0)
        minishell->exit_code = cd(cmd);
    else if (ft_strncmp(cmd->cmd_name, "pwd", 3) == 0)
        minishell->exit_code = pwd(cmd);
    else if (ft_strncmp(cmd->cmd_name, "env", 3) == 0)
        minishell->exit_code = env(cmd, minishell);
    else if (ft_strncmp(cmd->cmd_name, "echo", 4) == 0)
        minishell->exit_code = echo(cmd);
    else if (ft_strncmp(cmd->cmd_name, "export", 6) == 0)
        minishell->exit_code = export(cmd, minishell);
    else if (ft_strncmp(cmd->cmd_name, "unset", 5) == 0)
        minishell->exit_code = unset(cmd, minishell);
    else if (ft_strncmp(cmd->cmd_name, "exit", 4) == 0)
        printf("EXIT is still not done 😅\n");
    else
        return (0);
    return (1);
}