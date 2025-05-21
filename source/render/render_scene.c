/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:46:47 by ateca             #+#    #+#             */
/*   Updated: 2025/05/21 09:46:48 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	put_pixel(t_data *img, int x, int y, t_color color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = (color.r << 16 | color.g << 8 | color.b);
}

void	render_scene(t_scene *scene, t_data *img)
{
	int		x;
	int		y;
	t_vec3	origin;
	t_vec3	ray_dir;
	t_color	color;

	y = 0;
	origin = scene->camera.position;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray_dir = get_ray_direction(scene->camera, x, y);
			color = ray_trace(scene, origin, ray_dir);
			put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}
