#include "minishell.h"

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

char	**finish_paths_by_slash(char **raw_paths)
{
	int		nb;
	char	**correct_paths;

	nb = 0;
	while (raw_paths[nb])
		nb++;
	correct_paths = (char **)malloc(sizeof(char *) * (nb + 1));
	if (!correct_paths)
		return (NULL);
	nb = 0;
	while (raw_paths[nb])
	{
		correct_paths[nb] = ft_strjoin(raw_paths[nb], "/");
		nb++;
	}
	correct_paths[nb] = 0;
	return (correct_paths);
}
