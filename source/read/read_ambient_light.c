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
	if (scene->number_ambient_light >= 1)
	{
		printf("Error: Ambient light can only be defined once\n");
		exit_and_clear_gnl_buffer(line, fd);
	}
	scene->number_ambient_light = 1;
}
