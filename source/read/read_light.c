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

void	brightness_is_double(const char *str, char *line, int fd, char **tokens)
{
	if (ft_isdouble(str) == 0)
	{
		printf("Error: Brightness is not number: 'brightness': %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
}

void	read_light(char *line, int fd, t_scene *scene)
{
	char	**tokens;
	char	*brightness;

	tokens = ft_split(line, ' ');
	if (scene->number_light >= 1)
	{
		printf("Error: Light can only be defined once: %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	if (tokens == NULL || number_tokens(tokens) != 3 || tokens[0] == NULL
		|| tokens[2] == NULL)
	{
		printf("Error: Light format: 'L position brightness': %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	brightness = tokens[2];
	brightness_is_double(brightness, line, fd, tokens);
	scene->light.brightness = ft_atof(brightness);
	scene->number_light = 1;
	free_tokens(tokens);
}
