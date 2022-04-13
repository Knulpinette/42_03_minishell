#include "minishell.h"

/*
** 🦕🌴
** get_cmd_paths
**
** This function get all the different paths to functions from
** the environement variable (envp).
**
** The envp looks like this :
**					NAME=localname
**					HOST=localhost
**					PATH=all_the_paths:path:path:path
**					WHATEVER=whatever
**
** We only want the paths and we want all of them seperately so we
** use ft_split with ':' as the separator and an offset of 5 to start
** after 'PATH='. Then, because they'll need a '/' before we add the 
** command name to those paths, we add it already.
** 🌴🥥
*/

char	**get_cmd_paths(char **envp)
{
	char	**raw_paths;
	char	**paths;

	while (*envp && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	raw_paths = ft_split((*envp + 5), ':');
	paths = finish_paths_by_slash(raw_paths);
	free_split(raw_paths);
	return (paths);
}

/*
** finish_paths_by_slash
**
** Very self explanatory, this function adds a '/' at the
** end of every single paths retrieved in the previous function.
*/

char	**finish_paths_by_slash(char **raw_paths)
{
	int		nb;
	char	**correct_paths;

	nb = 0;
	while (raw_paths[nb])
		nb++;
	correct_paths = calloc_or_exit(sizeof(char *), nb + 1);
	nb = 0;
	while (raw_paths[nb])
	{
		correct_paths[nb] = ft_strjoin(raw_paths[nb], "/");
		nb++;
	}
	correct_paths[nb] = 0;
	return (correct_paths);
}
