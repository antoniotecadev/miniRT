/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:10:01 by achivela          #+#    #+#             */
/*   Updated: 2025/06/16 17:10:07 by achivela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../include/minirt.h"

static double quadratic_formula(double a, double b, double c)
{
        double  distance1;
        double distance2;
        double descriminant;
 
        descriminant = b * b - 4 * a * c;
        if (descriminant < 0)
                return (-1.0);
        distance1 = (-b - sqrt(descriminant)) / (2 * a);
        distance2 = (-b + sqrt(descriminant)) / (2 * a);
        if(distance1 > 0.0001)
                return (distance1);
        if(distance2 > 0.0001)
                return (distance2);
        return (-1.0);
}

double intersect_cylinder(t_vec3 origin, t_vec3 ray_direction, t_cylinder *cylinder)
{
    t_vec3 oc = vec3_sub(origin, cylinder->center);
    double radius = cylinder->diameter;
    
    double a = ray_direction.x * ray_direction.x + ray_direction.z * ray_direction.z;
    double b = 2.0 * (oc.x * ray_direction.x + oc.z * ray_direction.z);
    double c = oc.x * oc.x + oc.z * oc.z - radius;

    double t = quadratic_formula(a, b, c);
    if (t < 0.0001)
        return (-1.0);

    double y = origin.y + t * ray_direction.y;
    if (y < cylinder->center.y || y > cylinder->center.y + cylinder->height)
    {
        double discriminant = b * b - 4 * a * c;
        double t2 = (-b + sqrt(discriminant)) / (2 * a);
        if (t2 < 0.0001)
            return (-1.0);
        y = origin.y + t2 * ray_direction.y;
        if (y < cylinder->center.y || y > cylinder->center.y + cylinder->height)
            return (-1.0);
        t = t2;
    }

    return (t);
}
