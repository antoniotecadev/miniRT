/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_position.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:09:51 by ateca             #+#    #+#             */
/*   Updated: 2025/05/19 15:48:13 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void	is_valid(char *line, int fd, char **position_token, char **tokens)
{
	int	result;

	result = 0;
	if (position_token == NULL || number_tokens(position_token) != 3
		|| position_token[0] == NULL || position_token[1] == NULL
		|| position_token[2] == NULL)
	{
		result = 1;
		printf("Error: Position format: 'X,Y,Z': %s", line);
	}
	else if (!ft_isdouble(position_token[0]) || !ft_isdouble(position_token[1])
		|| !ft_isdouble(position_token[2]))
	{
		result = 1;
		printf("Error: Position is not number: 'X,Y,Z': %s", line);
	}
	if (result == 1)
	{
		free_tokens(position_token);
		free_tokens(tokens);
		free_gnl_buffer_and_exit(line, fd);
	}
}

t_vec3	get_position(char *xyz, char *line, int fd, char **tokens)
{
	t_vec3	position;
	char	**position_tokens;

	position_tokens = ft_split(xyz, ',');
	is_valid(line, fd, position_tokens, tokens);
	position.x = ft_atof(position_tokens[0]);
	position.y = ft_atof(position_tokens[1]);
	position.z = ft_atof(position_tokens[2]);
	free_tokens(position_tokens);
	return (position);
}
