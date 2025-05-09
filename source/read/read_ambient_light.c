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

void	color_format_is_valid(char *line, int fd, char **color_tokens, char **tokens)
{
	if (color_tokens == NULL || number_tokens(color_tokens) != 3 
		|| color_tokens[0] == NULL || color_tokens[1] == NULL 
			|| color_tokens[2] == NULL)
	{
		printf("Error: Color format: 'R,G,B': %s", line);
		free_tokens(color_tokens);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
}

t_color	read_color(char *line, int fd, char *rgb, char **tokens)
{
	t_color	color;
	char	*red;
	char	*green;
	char	*blue;
	char	**color_tokens;

	color_tokens = ft_split(rgb, ',');
	red = color_tokens[0];
	green = color_tokens[1];
	blue = color_tokens[2];
	color_format_is_valid(line, fd, color_tokens, tokens);
	color.r = ft_atoi(red);
	color.g = ft_atoi(green);
	color.b = ft_atoi(blue);
	free_tokens(color_tokens);
	return (color);
}

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
	scene->ambient_light.color = read_color(line, fd, tokens[2], tokens);
	scene->number_ambient_light = 1;
	free_tokens(tokens);
}
