#ifndef UTILS_H
# define UTILS_H

/* Main utils */
t_minishell		*get_minishell(t_minishell *minishell);
t_minishell		*init_minishell(char **envp);
void			*calloc_or_exit(size_t size, int count);

/* Parsing utils */
t_cmd_table		**init_cmd_table(int nb_cmd);
int				get_split_len(char **split);
char			*skip_space(char *line);
char			**get_cmd_paths(char **envp);
char			**finish_paths_by_slash(char **raw_paths);

/* Memory utils */
void			free_minishell(t_minishell *minishell);
void			free_split(char **split);
void			free_table(t_cmd_table **cmd_table);

/* Error utils */
int				error_and_exit(t_error code);
void			error_message(t_error code);
int				open_or_exit(char *file_path, mode_t mode);

#endif
