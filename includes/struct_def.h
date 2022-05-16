#ifndef STRUCT_DEF_H
# define STRUCT_DEF_H

/* PARSING MACROS */
# define PROMPT "🥥🐚 > "
# define SPACE ' '
# define PIPE '|'
# define SGL_QUOTE '\''
# define DBL_QUOTE '"'

typedef struct s_env {
	char			*name;
	char			*value;
}				t_env;

typedef enum e_token_type
{
	WORD,
	CMD,
	FLAG,
	ENV_VAR,
	REDIR,
}				t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*text;
}				t_token;

typedef enum e_redir_type
{
	OP_REDIR_IN,
	OP_REDIR_OUT,
	OP_DELIMITER,
	OP_APPEND,
}				t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	bool			quote;
	char			*arg;
}				t_redir;

typedef struct s_command_table
{
	bool		called_signal_heredoc;
	int			nb_redirs;
	t_redir		*redirs;
	int			nb_tokens;
	t_token		*tokens;
	char		*cmd_name;
	char		**flags;
	char		**cmd_args;
	char		*cmd_path;
	int			fd_in;
	int			is_infile_tmp;
	char		*infile_tmp;
	int			fd_out;
}				t_cmd_table;

/* see
 * https://www.cyberciti.biz/faq/linux-bash-exit-status-set-exit-statusin-bash/
 */
# define EXIT_NOT_FOUND 127
# define EXIT_SIGINT 130
# define EXIT_SIGQUIT 131
# define EXIT_ERROR 255
# define SYNTAX_ERROR 258

/* error codes for personalised error messages */
typedef enum e_error_codes
{
	ERR_NO_PRINT,
	MEMORY_FAIL,
	WRONG_ARGC,
	OPEN_FAIL,
	CLOSE_FAIL,
	PIPE_FAIL,
	WRITE_FAIL,
	WRONG_DIR,
	NO_OLDPWD,
	INVALID_IDENTIFIER,
	REDIR_NO_ARG,
	FORK_FAIL,
	CMD_NOT_FOUND,
	FILE_NOT_FOUND,
	TOO_MANY_ARGS,
	NON_NUM_ARG,
	TERMCAP_ERROR,
	SIGNAL_ERROR,
	UNLINK_FAIL
}				t_error;

typedef enum e_status
{
	INIT,
	RESET,
	CHILD_PROCESS,
	HEREDOC,
}			t_status;

typedef enum e_mode
{
	INTERACTIVE,
	NON_INTERACTIVE,
}			t_mode;

typedef struct s_minishell
{
	t_mode		mode;
	int			nb_cmds;
	char		**instructions;
	t_list		*env;
	char		**env_paths;
	t_cmd_table	*cmd_table;
	pid_t		*child_pids;
	t_cmd_table	*pointer_for_signal_heredoc;
	int			exit_code;
}				t_minishell;

#endif
