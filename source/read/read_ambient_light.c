/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ambient_light.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:57:45 by ateca             #+#    #+#             */
/*   Updated: 2025/05/07 12:03:14 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	read_ambient_light(char *line, int fd, t_scene *scene)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (scene->number_ambient_light >= 1)
	{
		printf("Error: Ambient light can only be defined once: %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	if (tokens == NULL || number_tokens(tokens) != 3
		|| tokens[0] == NULL || tokens[1] == NULL || tokens[2] == NULL)
	{
		printf("Error: Ambient Light format: 'A ratio R,G,B': %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	scene->ambient_light.ratio = ft_atof(tokens[1]);
	printf("ratio: %f\n", scene->ambient_light.ratio);
	scene->number_ambient_light = 1;
	free_tokens(tokens);
}
