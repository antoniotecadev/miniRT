/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:48:04 by ateca             #+#    #+#             */
/*   Updated: 2025/05/15 15:48:06 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	read_sphere(char *line, int fd, t_scene *scene)
{
	char	**tokens;
	char	*center;

	tokens = ft_split(line, ' ');
	if (tokens == NULL || number_tokens(tokens) != 4 || tokens[0] == NULL
		|| tokens[1] == NULL || tokens[2] == NULL || tokens[3] == NULL)
	{
		printf("Error: Sphere format: 'sp center diameter color': %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	center = tokens[1];
	scene->sphere.center = read_position(center, line, fd, tokens);
	free_tokens(tokens);
}
