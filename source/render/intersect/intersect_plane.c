/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:42:24 by achivela          #+#    #+#             */
/*   Updated: 2025/06/16 14:42:27 by achivela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../include/minirt.h"

double intersect_plane(t_vec3 origin, t_vec3 ray_direction, t_plane *plane)
{
    double denominator;
    double t;
    t_vec3 to_plane;
    
    denominator = vec3_dot(ray_direction, plane->normal);
    
    if (fabs(denominator) < 0.0001)
        return (-1.0);
    
    to_plane = vec3_sub(plane->point, origin);
    
    t = vec3_dot(to_plane, plane->normal) / denominator;
    

    if (t > 0.0001)
        return (t);
    
    return (-1.0);
}

