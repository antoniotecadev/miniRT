/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:41:43 by ateca             #+#    #+#             */
/*   Updated: 2025/05/07 11:41:45 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	free_gnl_buffer_and_exit(char *line, int fd)
{
	char	*buffer;

	free(line);
	while (1)
	{
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
		free(buffer);
	}
	close(fd);
	exit(1);
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens != NULL && tokens[i] != NULL)
	{
		free(tokens[i]);
		tokens[i] = NULL;
		i++;
	}
	free(tokens);
}
