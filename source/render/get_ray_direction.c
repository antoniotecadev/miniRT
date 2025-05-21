/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ray_direction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:25:14 by ateca             #+#    #+#             */
/*   Updated: 2025/05/21 10:25:17 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vec3	get_up_world(t_vec3 forward)
{
	if (fabs(forward.x) == 0 && fabs(forward.z) == 0)
		return ((t_vec3){0, 0, 1});
	else
		return ((t_vec3){0, 1, 0});
}

t_vec3	get_ray_direction(t_camera camera, int i, int j)
{
	double		aspect_ratio;
	double		fov_rad;
	double		viewport_height;
	double		viewport_width;
	t_ray_var	v;

	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	fov_rad = camera.fov * M_PI / 180.0;
	viewport_height = 2.0 * tan(fov_rad / 2.0);
	viewport_width = viewport_height * aspect_ratio;
	v.x = (double)i / (WIDTH - 1);
	v.y = (double)j / (HEIGHT - 1);
	v.x = (v.x - 0.5) * viewport_width;
	v.y = (0.5 - v.y) * viewport_height;
	v.forward = camera.direction;
	v.up_world = get_up_world(v.forward);
	v.right = vec3_normalize(vec3_cross(v.forward, v.up_world));
	v.up = vec3_normalize(vec3_cross(v.right, v.forward));
	v.direction = (t_vec3){
		v.forward.x + v.x * v.right.x + v.y * v.up.x,
		v.forward.y + v.x * v.right.y + v.y * v.up.y,
		v.forward.z + v.x * v.right.z + v.y * v.up.z
	};
	return (vec3_normalize(v.direction));
}
