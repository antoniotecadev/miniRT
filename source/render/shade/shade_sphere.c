/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:54:56 by ateca             #+#    #+#             */
/*   Updated: 2025/05/21 18:54:58 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minirt.h"

t_color	get_ambient_color_s(t_scene *scene, t_color_result result)
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

t_color	get_color_final_s(t_color_result result)
{
	return ((t_color){
		fmin(255, result.ambient.r + result.diffuse.r),
		fmin(255, result.ambient.g + result.diffuse.g),
		fmin(255, result.ambient.b + result.diffuse.b)
	});
}

t_color	shade_sphere(t_scene *scene, t_sphere *sphere, t_shade_object s)
{
	t_vec3			hit_point;
	t_vec3			normal;
	t_vec3			light_dir;
	t_vec3			shadow_origin;
	t_color_result	r;

	r.diff = 0.0;
	hit_point = vec3_add(s.origin, vec3_scale(s.ray_dir, s.distance_min));
	normal = vec3_normalize(vec3_sub(hit_point, sphere->center));
	light_dir = vec3_normalize(vec3_sub(scene->light.position, hit_point));
	r.light_distance = vec3_length(vec3_sub(scene->light.position, hit_point));
	shadow_origin = vec3_add(hit_point, vec3_scale(normal, 0.001));
	if (!is_in_shadow(scene, shadow_origin, light_dir, r.light_distance))
		r.diff = fmax(0.0, vec3_dot(normal, light_dir))
			* scene->light.brightness;
	r.color = sphere->color;
	r.diffuse = (t_color){
		(int)(r.color.r * r.diff),
		(int)(r.color.g * r.diff),
		(int)(r.color.b * r.diff)
	};
	r.ambient = get_ambient_color_s(scene, r);
	r.finale = get_color_final_s(r);
	return (r.finale);
}
