/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:31:51 by ateca             #+#    #+#             */
/*   Updated: 2025/05/21 10:31:52 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

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

t_color	shade_object(t_scene *scene, t_object_list *obj, t_shade_object s)
{
	(void)scene;
	(void)s;
	if (obj && obj->type == SPHERE)
		return (shade_sphere(scene, (t_sphere *)obj->object, s.origin, s.ray_dir, s.distance_min));
	//if (obj && obj->type == SPHERE)
	//	return (((t_sphere *)obj->object)->color);
	// if (obj && obj->type == PLANE)
	//	return ((t_plane *)obj->object)->color;
	// if (obj && obj->type == CYLINDER)
	//	return ((t_cylinder *)obj->object)->color;
	//return (((t_sphere *)obj->object)->color);
	return ((t_color){30, 30, 30});
}

double	hit_object(t_object_list *obj, t_vec3 origin, t_vec3 dir)
{
	if (obj->type == SPHERE)
		return (intersect_sphere(origin, dir, (t_sphere *)obj->object));
	// else if (obj->type == PLANE)
	// 	return (intersect_plane(origin, dir, (t_plane *)obj->object));
	// else if (obj->type == CYLINDER)
	// 	return (intersect_cylinder(origin, dir, (t_cylinder *)obj->object));
	return (-1.0);
}

t_color	ray_trace(t_scene *scene, t_vec3 origin, t_vec3 ray_dir)
{
	t_object_list	*obj;
	t_object_list	*closest_obj;
	double			distance_ray;
	double			distance_min;
	t_shade_object	shade;

	closest_obj = NULL;
	distance_min = DBL_MAX;
	obj = scene->object_list;
	while (obj)
	{
		distance_ray = hit_object(obj, origin, ray_dir);
		if (distance_ray > 0.0001 && distance_ray < distance_min)
		{
			distance_min = distance_ray;
			closest_obj = obj;
		}
		obj = obj->next;
	}
	shade.origin = origin;
	shade.ray_dir = ray_dir;
	shade.distance_min = distance_min;
	return (shade_object(scene, closest_obj, shade));
}
