/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:50:33 by ateca             #+#    #+#             */
/*   Updated: 2025/05/19 12:50:35 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

double	read_diameter_cy(char *diameter, char *line, int fd, char **tokens)
{
	if (ft_isdouble(diameter) == 0)
	{
		printf("Error: Cyinder diameter is not number: %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	return (ft_atof(diameter));
}

double	read_height_cy(char *height, char *line, int fd, char **tokens)
{
	if (ft_isdouble(height) == 0)
	{
		printf("Error: Cyinder height is not number: %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	return (ft_atof(height));
}

void	axi_is_valid(char *line, int fd, char **axis_tokens, char **tokens)
{
	int	result;

	result = 0;
	if (axis_tokens == NULL || number_tokens(axis_tokens) != 3
		|| axis_tokens[0] == NULL || axis_tokens[1] == NULL
		|| axis_tokens[2] == NULL)
	{
		result = 1;
		printf("Error: Axi cylinder format: 'X,Y,Z': %s", line);
	}
	else if (!ft_isdouble(axis_tokens[0]) || !ft_isdouble(axis_tokens[1])
		|| !ft_isdouble(axis_tokens[2]))
	{
		result = 1;
		printf("Error: Axi cylinder is not number: 'X,Y,Z': %s", line);
	}
	if (result == 1)
	{
		free_tokens(axis_tokens);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
}

t_vec3	read_axis(char *xyz, char *line, int fd, char **tokens)
{
	t_vec3	axi;
	char	**axis_tokens;

	axis_tokens = ft_split(xyz, ',');
	axi_is_valid(line, fd, axis_tokens, tokens);
	axi.x = ft_atof(axis_tokens[0]);
	axi.y = ft_atof(axis_tokens[1]);
	axi.z = ft_atof(axis_tokens[2]);
	free_tokens(axis_tokens);
	if (axi.x < -1.0 || axi.x > 1.0 || axi.y < -1.0 || axi.y > 1.0
		|| axi.z < -1.0 || axi.z > 1.0)
	{
		printf("Error: Axi cylinder must be in the range [-1,1]: %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	axi = vec3_normalize(axi);
	if (axi.x == 0 && axi.y == 0 && axi.z == 0)
	{
		printf("Error: Axi cylinder cannot be zeros: %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	return (axi);
}

void	read_cylinder(char *line, int fd, t_scene *scene)
{
	char	**tokens;
	char	*center;
	char	*axis;
	char	*diameter;
	char	*height;

	tokens = ft_split(line, ' ');
	if (tokens == NULL || number_tokens(tokens) != 6 || tokens[0] == NULL
		|| tokens[1] == NULL || tokens[2] == NULL || tokens[3] == NULL
		|| tokens[4] == NULL || tokens[5] == NULL)
	{
		printf("Error: Cy format: 'cy center axis dia hei color': %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	center = tokens[1];
	axis = tokens[2];
	diameter = tokens[3];
	height = tokens[4];
	scene->cylinder.center = read_position(center, line, fd, tokens);
	scene->cylinder.axis = read_axis(axis, line, fd, tokens);
	scene->cylinder.diameter = read_diameter_cy(diameter, line, fd, tokens);
	scene->cylinder.height = read_height_cy(height, line, fd, tokens);
	scene->cylinder.color = read_color(line, fd, tokens[5], tokens);
	free_tokens(tokens);
}
