/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:51:52 by ateca             #+#    #+#             */
/*   Updated: 2025/05/19 15:47:36 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static double	get_field_iew(char *fov_str, char *line, int fd, char **tokens)
{
	double	fov;

	if (ft_isdouble(fov_str) == 0)
	{
		printf("Error: FOV for camera is not number: %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	fov = ft_atof(fov_str);
	if (fov < 0.0 || fov > 180.0)
	{
		printf("Error: FOV for camera must be in the range [0,180]: %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	return (fov);
}

static void	dr_is_valid(char *line, int fd, char **direc_tokens, char **tokens)
{
	int	result;

	result = 0;
	if (direc_tokens == NULL || number_tokens(direc_tokens) != 3
		|| direc_tokens[0] == NULL || direc_tokens[1] == NULL
		|| direc_tokens[2] == NULL)
	{
		result = 1;
		printf("Error: Direction camera format: 'X,Y,Z': %s", line);
	}
	else if (!ft_isdouble(direc_tokens[0]) || !ft_isdouble(direc_tokens[1])
		|| !ft_isdouble(direc_tokens[2]))
	{
		result = 1;
		printf("Error: Direction camera is not number: 'X,Y,Z': %s", line);
	}
	if (result == 1)
	{
		free_tokens(direc_tokens);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
}

static t_vec3	get_direction(char *xyz, char *line, int fd, char **tokens)
{
	t_vec3	direction;
	char	**direction_tokens;

	direction_tokens = ft_split(xyz, ',');
	dr_is_valid(line, fd, direction_tokens, tokens);
	direction.x = ft_atof(direction_tokens[0]);
	direction.y = ft_atof(direction_tokens[1]);
	direction.z = ft_atof(direction_tokens[2]);
	free_tokens(direction_tokens);
	if (direction.x < -1.0 || direction.x > 1.0
		|| direction.y < -1.0 || direction.y > 1.0
		|| direction.z < -1.0 || direction.z > 1.0)
	{
		printf("Error: Direction must be in the range [-1,1]: %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	direction = vec3_normalize(direction);
	if (direction.x == 0 && direction.y == 0 && direction.z == 0)
	{
		printf("Error: Direction camera cannot be zeros: %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	return (direction);
}

void	camera(char *line, int fd, t_scene *scene)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (scene->number_camera >= 1)
	{
		printf("Error: Camera can only be defined once: %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	if (tokens == NULL || number_tokens(tokens) != 4 || tokens[0] == NULL
		|| tokens[1] == NULL || tokens[2] == NULL || tokens[3] == NULL)
	{
		printf("Error: Camera format: 'C position direction FOV': %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	scene->camera.position = get_position(tokens[1], line, fd, tokens);
	scene->camera.direction = get_direction(tokens[2], line, fd, tokens);
	scene->camera.fov = get_field_iew(tokens[3], line, fd, tokens);
	scene->number_camera = 1;
	free_tokens(tokens);
}
