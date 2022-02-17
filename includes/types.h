#ifndef TYPES_H
# define TYPES_H

typedef struct 	s_minishell
{
	char* coconut;
}				t_minishell;

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