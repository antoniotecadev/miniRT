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

void	exit_and_clear_gnl_buffer(char *line, int fd)
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
