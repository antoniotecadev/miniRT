/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:50:33 by ateca             #+#    #+#             */
/*   Updated: 2025/05/19 15:47:47 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static double	get_diameter(char *diameter, char *line, int fd, char **tokens)
{
	if (ft_isdouble(diameter) == 0)
	{
		printf("Error: Cyinder diameter is not number: %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	return (ft_atof(diameter));
}

static double	get_height(char *height, char *line, int fd, char **tokens)
{
	if (ft_isdouble(height) == 0)
	{
		printf("Error: Cyinder height is not number: %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	return (ft_atof(height));
}

static void	axi_is_valid(char *line, int fd, char **axis_tokens, char **tokens)
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

static t_vec3	get_axis(char *xyz, char *line, int fd, char **tokens)
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

void	cylinder(char *line, int fd, t_scene *scene)
{
	char	**tokens;
	char	*diameter;
	char	*height;
	char	*color;
	t_cylinder *cylinder;
	
	tokens = ft_split(line, ' ');
	if (tokens == NULL || number_tokens(tokens) != 6 || tokens[0] == NULL
		|| tokens[1] == NULL || tokens[2] == NULL || tokens[3] == NULL
		|| tokens[4] == NULL || tokens[5] == NULL)
	{
		printf("Error: Cy format: 'cy center axis dia hei color': %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	diameter = tokens[3];
	height = tokens[4];
	color = tokens[5];
	scene->cylinder.center = get_position(tokens[1], line, fd, tokens);
	scene->cylinder.axis = get_axis(tokens[2], line, fd, tokens);
	scene->cylinder.diameter = get_diameter(diameter, line, fd, tokens);
	scene->cylinder.height = get_height(height, line, fd, tokens);
	scene->cylinder.color = get_color(line, fd, color, tokens);
	free_tokens(tokens);
	scene->number_cylinder++;
	cylinder = malloc(sizeof(t_cylinder));
	*cylinder = scene->cylinder;
	add_object_to_list(scene,CYLINDER, cylinder);
}
