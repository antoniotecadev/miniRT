/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:28:57 by ateca             #+#    #+#             */
/*   Updated: 2025/05/19 10:28:58 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	normal_is_valid(char *line, int fd, char **normal_tokens, char **tokens)
{
	int	result;

	result = 0;
	if (normal_tokens == NULL || number_tokens(normal_tokens) != 3
		|| normal_tokens[0] == NULL || normal_tokens[1] == NULL
		|| normal_tokens[2] == NULL)
	{
		result = 1;
		printf("Error: Normal plane format: 'X,Y,Z': %s", line);
	}
	else if (!ft_isdouble(normal_tokens[0])
		|| !ft_isdouble(normal_tokens[1])
		|| !ft_isdouble(normal_tokens[2]))
	{
		result = 1;
		printf("Error: Normal plane is not number: 'X,Y,Z': %s", line);
	}
	if (result == 1)
	{
		free_tokens(normal_tokens);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
}

t_vec3	read_normal(char *xyz, char *line, int fd, char **tokens)
{
	t_vec3	normal;
	char	**normal_tokens;

	normal_tokens = ft_split(xyz, ',');
	normal_is_valid(line, fd, normal_tokens, tokens);
	normal.x = ft_atof(normal_tokens[0]);
	normal.y = ft_atof(normal_tokens[1]);
	normal.z = ft_atof(normal_tokens[2]);
	free_tokens(normal_tokens);
	if (normal.x < -1.0 || normal.x > 1.0
		|| normal.y < -1.0 || normal.y > 1.0
		|| normal.z < -1.0 || normal.z > 1.0)
	{
		printf("Error: Normal plane must be in the range [-1,1]: %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	normal = vec3_normalize(normal);
	if (normal.x == 0 && normal.y == 0 && normal.z == 0)
	{
		printf("Error: Normal plane cannot be zeros: %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	return (normal);
}

void	read_plane(char *line, int fd, t_scene *scene)
{
	char	**tokens;
	char	*point;
	char	*normal;
	char	*color;

	tokens = ft_split(line, ' ');
	if (tokens == NULL || number_tokens(tokens) != 4 || tokens[0] == NULL
		|| tokens[1] == NULL || tokens[2] == NULL || tokens[3] == NULL)
	{
		printf("Error: Plane format: 'pl point normal color': %s", line);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	point = tokens[1];
	normal = tokens[2];
	color = tokens[3];
	scene->plane.point = read_position(point, line, fd, tokens);
	scene->plane.normal = read_normal(normal, line, fd, tokens);
	scene->plane.color = read_color(line, fd, color, tokens);
	free_tokens(tokens);
	scene->number_plane++;
}
