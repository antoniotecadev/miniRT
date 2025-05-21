/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:41:43 by ateca             #+#    #+#             */
/*   Updated: 2025/05/07 11:41:45 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	free_gnl_buffer_and_exit(char *line, int fd)
{
	char	*buffer;

	free(line);
	while (1)
	{
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
		free(buffer);
	}
	close(fd);
	exit(1);
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens != NULL && tokens[i] != NULL)
	{
		free(tokens[i]);
		tokens[i] = NULL;
		i++;
	}
	free(tokens);
}

void	free_objects(t_object_list *object_list)
{
	t_object_list	*next;
	t_object_list	*current;

	current = object_list;
	while (current != NULL)
	{
		next = current->next;
		free(current->object);
		free(current);
		current = next;
	}
}

void	free_mlx(t_data *img)
{
	if (img->img)
		mlx_destroy_image(img->mlx, img->img);
	if (img->win)
		mlx_destroy_window(img->mlx, img->win);
	if (img->mlx)
	{
		mlx_destroy_display(img->mlx);
		free(img->mlx);
	}
	exit(0);
}
