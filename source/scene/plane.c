/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:41:36 by achivela          #+#    #+#             */
/*   Updated: 2025/06/16 14:41:38 by achivela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void	is_valid(char *line, int fd, char **normal_tokens, char **tokens)
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

static t_vec3	get_normal(char *xyz, char *line, int fd, char **tokens)
{
	t_vec3	normal;
	char	**normal_tokens;

	normal_tokens = ft_split(xyz, ',');
	is_valid(line, fd, normal_tokens, tokens);
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

void	plane(char *line, int fd, t_scene *scene)
{
	char	**tokens;
	char	*point;
	char	*normal;
	char	*color;
	t_plane	*plane;

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
	scene->plane.point = get_position(point, line, fd, tokens);
	scene->plane.normal = get_normal(normal, line, fd, tokens);
	scene->plane.color = get_color(line, fd, color, tokens);
	free_tokens(tokens);
	scene->number_plane++;
    plane = malloc(sizeof(t_plane));
    *plane = scene->plane; 
    add_object_to_list(scene, PLANE, plane);
}
