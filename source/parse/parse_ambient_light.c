/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:57:45 by ateca             #+#    #+#             */
/*   Updated: 2025/05/06 15:57:46 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	parse_ambient_light(char *line, t_scene *scene)
{
	(void) line;
	if (scene->number_ambient_light >= 1)
	{
		printf("Error: Ambient light can only be defined once\n");
	}
	scene->number_ambient_light = 1;
}
