#ifndef UTILS_H
# define UTILS_H

/* Main utils */
t_minishell		*get_minishell(t_minishell *minishell);
t_minishell		*init_minishell(char **envp);
void			*calloc_or_exit(size_t size, int count);

/* Parsing utils */
t_cmd_table		*init_cmd_table(int nb_cmd);
int				get_nb_tokens(const char *s, char c);
int				get_nb_redirs(char *instructions);
int				quote_len(const char *s, char c, char quote, int i);
int				get_array_len(char **split);
char			*skip_space(char *line);
char			**get_cmd_paths(char **envp);
char			**finish_paths_by_slash(char **raw_paths);
/* env_var */
int				get_env_var_len(char *text, char delim);
char			*get_env_var(char *text, int env_var_count, char delim);

/* Memory utils */
void			free_minishell(t_minishell *minishell);
void			free_split(char **split);
void			free_table(t_cmd_table *cmd_table, int nb_cmd);
void			free_tokens(t_token *tokens, int nb_tokens);

/* Error utils */
int				error_and_exit(t_error code);
void			error_message(t_error code);
int				open_or_exit(char *file_path, mode_t mode);

#endif
