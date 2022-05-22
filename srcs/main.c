/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 22:36:16 by svieira           #+#    #+#             */
/*   Updated: 2022/05/22 22:36:26 by svieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int					fd;
	char				*line;
	t_minishell			*minishell;
	int					exit_code;

	set_termcaps();
	if (argc > 2)
		error_and_exit(WRONG_ARGC);
	fd = 0;
	if (argc == 2)
		fd = open_or_exit(argv[1], O_RDONLY);
	minishell = init_minishell(envp, argc);
	set_signals(INIT, minishell->mode);
	while (1)
	{
		line = get_instructions_line(minishell->mode, fd);
		if (!line)
			break ;
		exit_code = parse(line);
		free(line);
		if (exit_code != SYNTAX_ERROR && minishell->nb_cmds)
			exit_code = execute(minishell);
	}
	free_minishell(minishell);
	return (exit_code);
}
