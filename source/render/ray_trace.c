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

t_color	shade_object(t_scene *scene, t_object_list *obj, t_shade_object shade)
{
	if (obj && obj->type == SPHERE)
		return (shade_sphere(scene, (t_sphere *)obj->object, shade));
	if (obj && obj->type == PLANE)
		return (shade_plane(scene, (t_plane *)obj->object, shade));
	if (obj && obj->type == CYLINDER)
		return (shade_cylinder(scene, (t_cylinder *)obj->object, shade));
	return ((t_color){10, 10, 10});
}

double	hit_object(t_object_list *obj, t_vec3 origin, t_vec3 dir)
{
	if (obj->type == SPHERE)
		return (intersect_sphere(origin, dir, (t_sphere *)obj->object));
	else if (obj->type == PLANE)
		return (intersect_plane(origin, dir, (t_plane *)obj->object));
	else if (obj->type == CYLINDER)
		return (intersect_cylinder(origin, dir, (t_cylinder *)obj->object));
	return (-1.0);
}

int	is_in_shadow(t_scene *scene, t_vec3 origin, t_vec3 light_dir,
		double max_distance)
{
	double			distance_ray;
	t_object_list	*obj;

	obj = scene->object_list;
	while (obj)
	{
		distance_ray = hit_object(obj, origin, light_dir);
		if (distance_ray > 0.001 && distance_ray < max_distance)
			return (1);
		obj = obj->next;
	}
	return (0);
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
