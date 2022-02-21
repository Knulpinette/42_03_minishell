#ifndef TYPES_H
# define TYPES_H

typedef struct 	s_minishell
{
	char		*prompt;
	char		**envp_paths; // this is the split with all the paths from envp. We only need to get it once in the beginning. It will always be the same for the whole program.
	t_cmd_table	**cmd_table;

}				t_minishell;

/* PARSING MACROS */
# define SPACE ' '
# define PIPE '|'
# define ENV_VARIABLE '$'
# define QUOTE '''
# define DBL_QUOTE '"'
# define REDIR_IN '<'
# define REDIR_OUT '>'
# define DELIMITER "<<"
# define APPEND_MODE ">>"

typedef struct 	s_command_table
{
	char	*cmd;
	char	**flags;
	char	*cmd_path; // this will be the concenated "right"/correct path (or at least where we'll store the paths we want to test to see if they can be executed)
	int		infile_fd;
	char	*infile;
	int		outfile_fd;
	char	*outfile;
	bool	delimiter;
	char	*delim_arg;
	int		mode; /* OVERWRITE, APPEND */
	char	**args;

}				t_cmd_table;

typedef	enum	e_redir_mode // for readable instructions when you change the mode according to >>
{
	OVERWRITE, // default IS overwrite, right ? (here overwrite = 0)
	APPEND,
}				t_redir_mode;

/* see https://www.cyberciti.biz/faq/linux-bash-exit-status-set-exit-statusin-bash/ */
# define EXIT_FILE_NOT_FOUND 127

// error codes that we can use for the error function and making the whole thing clearer.
typedef enum 	e_error_codes
{
	ERR_NO_PRINT,
	MEMORY_FAIL,
	WRONG_ARGC,
}				t_error;


#endif