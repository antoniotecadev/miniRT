/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:28:59 by ateca             #+#    #+#             */
/*   Updated: 2025/05/21 17:29:01 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minirt.h"

static double	quadratic_formula(double a, double b, double c)
{
	double	distance1;
	double	distance2;
	double	discriminant;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1.0);
	distance1 = (-b - sqrt(discriminant)) / (2 * a);
	distance2 = (-b + sqrt(discriminant)) / (2 * a);
	if (distance1 > 0.0001)
		return (distance1);
	if (distance2 > 0.0001)
		return (distance2);
	return (-1.0);
}

double	intersect_sphere(t_vec3 ray_origin, t_vec3 ray_dir, t_sphere *sphere)
{
	t_vec3	oc;
	double	radius;
	double	a;
	double	b;
	double	c;

	oc = vec3_sub(ray_origin, sphere->center);
	radius = sphere->diameter / 2.0;
	a = vec3_dot(ray_dir, ray_dir);
	b = 2.0 * vec3_dot(oc, ray_dir);
	c = vec3_dot(oc, oc) - (radius * radius);
	return (quadratic_formula(a, b, c));
}
