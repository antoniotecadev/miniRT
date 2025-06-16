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

t_color shade_cylinder(t_scene *scene, t_cylinder *cylinder, t_vec3 origin, t_vec3 dir, double t)
{
    t_vec3 hit_point = vec3_add(origin, vec3_scale(dir, t));
    t_vec3 normal = {hit_point.x - cylinder->center.x, 0, hit_point.z - cylinder->center.z};
    normal = vec3_normalize(normal);
    t_vec3 light_dir = vec3_normalize(vec3_sub(scene->light.position, hit_point));

    double diff = fmax(0.0, vec3_dot(normal, light_dir)) * scene->light.brightness;

    t_color obj = cylinder->color;

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

    return (result);
}
