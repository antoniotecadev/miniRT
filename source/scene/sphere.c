/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:48:04 by ateca             #+#    #+#             */
/*   Updated: 2025/05/19 15:48:58 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

double	get_diameter(char *diameter, char *line, int fd, char **tokens)
{
	if (ft_isdouble(diameter) == 0)
	{
		printf("Error: Sphere diameter is not number: %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	return (ft_atof(diameter));
}

void	sphere(char *line, int fd, t_scene *scene)
{
	char	**tokens;
	char	*center;
	char	*diameter;
	char	*color;

	tokens = ft_split(line, ' ');
	if (tokens == NULL || number_tokens(tokens) != 4 || tokens[0] == NULL
		|| tokens[1] == NULL || tokens[2] == NULL || tokens[3] == NULL)
	{
		printf("Error: Sphere format: 'sp center diameter color': %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	center = tokens[1];
	diameter = tokens[2];
	color = tokens[3];
	scene->sphere.center = get_position(center, line, fd, tokens);
	scene->sphere.diameter = get_diameter(diameter, line, fd, tokens);
	scene->sphere.color = get_color(line, fd, color, tokens);
	free_tokens(tokens);
	scene->number_sphere++;
}
