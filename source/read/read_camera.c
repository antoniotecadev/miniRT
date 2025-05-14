/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:51:52 by ateca             #+#    #+#             */
/*   Updated: 2025/05/14 17:51:54 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	read_camera(char *line, int fd, t_scene *scene)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (scene->number_camera >= 1)
	{
		printf("Error: Camera can only be defined once: %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	if (tokens == NULL || number_tokens(tokens) != 4 || tokens[0] == NULL
		|| tokens[1] == NULL || tokens[2] == NULL || tokens[3] == NULL)
	{
		printf("Error: Camera format: 'C position direction FOV': %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	scene->camera.position = read_position(tokens[1], line, fd, tokens);
	scene->number_camera = 1;
	free_tokens(tokens);
}
