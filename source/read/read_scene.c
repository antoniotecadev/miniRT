/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:00:15 by ateca             #+#    #+#             */
/*   Updated: 2025/05/07 12:10:09 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	initialize_number_scene_element(t_scene *scene)
{
	scene->number_ambient_light = 0;
	scene->number_camera = 0;
	scene->number_light = 0;
}

void	check_scene_element(char *line, int *i, int fd, t_scene *scene)
{
	if (ft_strncmp(&line[*i], "A", 1) == 0)
		read_ambient_light(line, fd, scene);
	else if (ft_strncmp(&line[*i], "C", 1) == 0)
		read_camera(line, fd, scene);
	else if (ft_strncmp(&line[*i], "L", 1) == 0)
		read_light(line, fd, scene);
}

int	is_rt_extension(char *file)
{
	char	*dot;

	dot = ft_strrchr(file, '.');
	if (dot && ft_strcmp(dot, ".rt") == 0)
		return (1);
	return (0);
}

int	open_and_validate_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: File not found or unable to open\n");
		exit(2);
	}
	if (!is_rt_extension(file))
	{
		close(fd);
		printf("Error: Invalid file extension, expected .rt\n");
		exit(1);
	}
	return (fd);
}

void	read_scene(char *file, t_scene *scene)
{
	int		i;
	int		fd;
	char	*line;

	fd = open_and_validate_file(file);
	initialize_number_scene_element(scene);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strisspace(line))
		{
			free(line);
			continue ;
		}
		i = 0;
		while (line[i] && ft_isspace(line[i]))
			i++;
		check_scene_element(line, &i, fd, scene);
		free(line);
	}
	close(fd);
}
