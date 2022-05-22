/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 22:36:40 by svieira           #+#    #+#             */
/*   Updated: 2022/05/22 22:36:43 by svieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_instructions_line(t_mode mode, int fd)
{
	char	*line;
	int		nb_bits_read;

	if (mode == INTERACTIVE)
	{
		line = readline(PROMPT);
		if (line && ft_strlen(line) > 0)
			add_history(line);
	}
	else
		nb_bits_read = get_next_line(fd, &line);
	if (!line || (mode == NON_INTERACTIVE && nb_bits_read <= 0))
	{
		free(line);
		return (NULL);
	}
	return (line);
}
