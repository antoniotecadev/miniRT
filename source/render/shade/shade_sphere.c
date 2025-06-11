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

t_color shade_sphere(t_scene *scene, t_sphere *sphere,
	t_vec3 origin, t_vec3 dir, double t)
{
	t_vec3 hit_point = vec3_add(origin, vec3_scale(dir, t));
	t_vec3 normal = vec3_normalize(vec3_sub(hit_point, sphere->center));
	t_vec3 light_dir = vec3_normalize(vec3_sub(scene->light.position, hit_point));

	double diff = fmax(0.0, vec3_dot(normal, light_dir)) * scene->light.brightness;

	t_color obj = sphere->color;

	t_color diffuse = (t_color){
		(int)(obj.r * diff),
		(int)(obj.g * diff),
		(int)(obj.b * diff)
	};

	t_color ambient = (t_color){
		(int)(obj.r * scene->ambient_light.ratio * scene->ambient_light.color.r / 255.0),
		(int)(obj.g * scene->ambient_light.ratio * scene->ambient_light.color.g / 255.0),
		(int)(obj.b * scene->ambient_light.ratio * scene->ambient_light.color.b / 255.0)
	};

	t_color result = {
		fmin(255, ambient.r + diffuse.r),
		fmin(255, ambient.g + diffuse.g),
		fmin(255, ambient.b + diffuse.b)
	};

	return result;
}