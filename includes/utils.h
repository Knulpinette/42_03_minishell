#ifndef UTILS_H
# define UTILS_H

/* Minishell utils */
t_minishell		*get_minishell(t_minishell *minishell);
t_minishell		*init_minishell(char **envp);

/* ENV List */
t_env	*new_env_content(char *var);
t_list	*init_env_lst(char **envp);
void	del_env_content(void *env_var);
/* ENV List getters and setters */
char    *get_env_lst_name(t_list *env_lst);
char	*get_env_lst_value(t_list *env_lst);
t_list	*get_env_lst(t_list *env_lst, char *name);
char	*get_env_value(t_list *env_lst, char *name);
void	set_env_value(t_list *env_lst, char *name, char *value);

/* Array utils */
int		get_array_len(char **split);

/* Free Memory utils */
void	free_minishell(t_minishell *minishell);
void	free_split(char **split);
void	free_table(t_cmd_table *cmd_table, int nb_cmds);
void	free_tokens(t_token *tokens, int nb_tokens);

/* Error and/or Exit utils */
int		error_and_exit(t_error code);
void	error_message(t_error code);
int		open_or_exit(char *file_path, mode_t mode);
void	*calloc_or_exit(size_t size, int count);

#endif
