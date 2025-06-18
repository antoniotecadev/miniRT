/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:10:37 by achivela          #+#    #+#             */
/*   Updated: 2025/06/16 17:10:40 by achivela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../include/minirt.h"

t_color	get_ambient_color_c(t_scene *scene, t_color_result result)
{
	int	red;
	int	green;
	int	blue;

	red = (int)(result.color.r * scene->ambient_light.ratio
			* (scene->ambient_light.color.r / 255.0));
	green = (int)(result.color.g * scene->ambient_light.ratio
			* (scene->ambient_light.color.g / 255.0));
	blue = (int)(result.color.b * scene->ambient_light.ratio
			* (scene->ambient_light.color.b / 255.0));
	return ((t_color){red, green, blue});
}

t_vec3	get_normal(t_cylinder *cylinder, t_vec3 hit_point)
{
	return (vec3_normalize((t_vec3){
			hit_point.x - cylinder->center.x,
			0,
			hit_point.z - cylinder->center.z
		}));
}

t_color	shade_cylinder(t_scene *scene, t_cylinder *cylinder, t_shade_object s)
{
	t_vec3			hit_point;
	t_vec3			normal;
	t_vec3			light_dir;
	double			diff;
	t_color_result	result;

	hit_point = vec3_add(s.origin, vec3_scale(s.ray_dir, s.distance_min));
	normal = get_normal(cylinder, hit_point);
	light_dir = vec3_normalize(vec3_sub(scene->light.position, hit_point));
	diff = fmax(0.0, vec3_dot(normal, light_dir)) * scene->light.brightness;
	result.color = cylinder->color;
	result.diffuse = (t_color){
		(int)(result.color.r * diff),
		(int)(result.color.g * diff),
		(int)(result.color.b * diff)
	};
	result.ambient = get_ambient_color_c(scene, result);
	result.finale = (t_color){
		fmin(255, result.ambient.r + result.diffuse.r),
		fmin(255, result.ambient.g + result.diffuse.g),
		fmin(255, result.ambient.b + result.diffuse.b)
	};
	return (result.finale);
}
