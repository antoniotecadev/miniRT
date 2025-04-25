/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:00:15 by ateca             #+#    #+#             */
/*   Updated: 2025/04/23 17:00:18 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	is_rt_extension(char *file)
{
	char	*dot;

	dot = ft_strrchr(file, '.');
	if (dot && ft_strcmp(dot, ".rt") == 0)
		return (1);
	return (0);
}

void	open_and_validate_file(char *file, int *fd)
{
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
	{
		ft_putstr_fd("Error: File not found or unable to open\n", 2);
		exit(2);
	}
	if (!is_rt_extension(file))
	{
		close(*fd);
		ft_putstr_fd("Invalid file extension, expected .rt\n", 2);
		exit(2);
	}
}

void	parse_scene(char *file, t_scene *scene)
{
	int		fd;
	char	*line;

	(void)scene;
	open_and_validate_file(file, &fd);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strisspace(line))
		{
			ft_putstr_fd("line is empty\n", 1);
			free(line);
			continue ;
		}	
		free(line);
	}
	close(fd);
}
