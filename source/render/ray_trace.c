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

t_color	shade_object(t_scene *scene, t_object_list *obj, t_shade_object s)
{
	(void)scene;
	(void)s;
	if (obj && obj->type == SPHERE)
		return (((t_sphere *)obj->object)->color);
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
	t_shade_object	s;

	closest_obj = NULL;
	distance_min = 1e9;
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
	s.origin = origin;
	s.ray_dir = ray_dir;
	s.distance_min = distance_min;
	return (shade_object(scene, closest_obj, s));
}
