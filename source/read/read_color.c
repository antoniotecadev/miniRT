/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:01:59 by ateca             #+#    #+#             */
/*   Updated: 2025/05/12 14:02:01 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	format_is_valid(char *line, int fd, char **color_tokens, char **tokens)
{
	int	result;

	result = 0;
	if (color_tokens == NULL || number_tokens(color_tokens) != 3
		|| color_tokens[0] == NULL || color_tokens[1] == NULL
		|| color_tokens[2] == NULL)
	{
		result = 1;
		printf("Error: Color format: 'R,G,B': %s", line);
	}
	else if (!ft_isnumber(color_tokens[0]) || !ft_isnumber(color_tokens[1])
		|| !ft_isnumber(color_tokens[2]))
	{
		result = 1;
		printf("Error: Color is not number: 'R,G,B': %s", line);
	}
	if (result == 1)
	{
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
	format_is_valid(line, fd, color_tokens, tokens);
	color.r = ft_atoi(red);
	color.g = ft_atoi(green);
	color.b = ft_atoi(blue);
	if (color.r < 0 || color.r > 255 || color.g < 0 || color.g > 255
		|| color.b < 0 || color.b > 255)
	{
		printf("Error: Color must be in the range 0-255: 'R,G,B': %s", line);
		free_tokens(color_tokens);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
	free_tokens(color_tokens);
	return (color);
}
