/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:36:18 by ateca             #+#    #+#             */
/*   Updated: 2025/05/14 13:36:20 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

double	read_brightness(char *brightness, char *line, int fd, char **tokens)
{
	double	bright;

	if (ft_isdouble(brightness) == 0)
	{
		printf("Error: Light brightness is not number: %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	bright = ft_atof(brightness);
	if (bright < 0.0 || bright > 1.0)
	{
		printf("Error: Brightness must be in the range [0.0,1.0]: %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	return (bright);
}

void	read_light(char *line, int fd, t_scene *scene)
{
	char	**tokens;
	char	*position;
	char	*brightness;

	tokens = ft_split(line, ' ');
	if (scene->number_light >= 1)
	{
		printf("Error: Light can only be defined once: %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	if (tokens == NULL || number_tokens(tokens) != 3 || tokens[0] == NULL
		|| tokens[1] == NULL || tokens[2] == NULL)
	{
		printf("Error: Light format: 'L position brightness': %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	position = tokens[1];
	brightness = tokens[2];
	scene->light.brightness = read_brightness(brightness, line, fd, tokens);
	scene->light.position = read_position(position, line, fd, tokens);
	scene->number_light = 1;
	free_tokens(tokens);
}
