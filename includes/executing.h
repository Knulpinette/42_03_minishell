#ifndef EXECUTING_H
# define EXECUTING_H

/* EXECUTOR */
int	execute(t_minishell *minishell);

/* EXECUTE REDIRECTIONS */
int	exec_redirs(t_cmd_table *cmd);

/* EXECUTE COMMANDS */
int exec_builtin(t_minishell *minishell, t_cmd_table *cmd);
int exec_system(t_minishell *minishell, t_cmd_table *cmd);

#endif