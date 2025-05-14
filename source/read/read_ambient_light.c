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

double	read_ratio(double ratio, char *line, int fd, char **tokens)
{
	if (ratio < 0.0 || ratio > 1.0)
	{
		printf("Error: Ratio must be in the range [0.0,1.0]: %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	return (ratio);
}

void	ratio_is_double(const char *str, char *line, int fd, char **tokens)
{
	if (ft_isdouble(str) == 0)
	{
		printf("Error: Ratio is not number: 'ratio': %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
}

void	read_ambient_light(char *line, int fd, t_scene *scene)
{
	char	**tokens;
	char	*ratio;
	char	*color;

	tokens = ft_split(line, ' ');
	if (scene->number_ambient_light >= 1)
	{
		printf("Error: Ambient light can only be defined once: %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	if (tokens == NULL || number_tokens(tokens) != 3 || tokens[0] == NULL
		|| tokens[1] == NULL || tokens[2] == NULL)
	{
		printf("Error: Ambient Light format: 'A ratio R,G,B': %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	ratio = tokens[1];
	color = tokens[2];
	ratio_is_double(ratio, line, fd, tokens);
	scene->ambient_light.ratio = read_ratio(ft_atof(ratio), line, fd, tokens);
	scene->ambient_light.color = read_color(line, fd, color, tokens);
	scene->number_ambient_light = 1;
	free_tokens(tokens);
}
