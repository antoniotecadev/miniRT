#include "../../../include/minirt.h"

t_color shade_plane(t_scene *scene, t_plane *plane, t_vec3 origin, t_vec3 dir, double t)
{
    t_vec3 hit_point;
    t_vec3 normal;
    t_vec3 light_dir;
    double diff;
    t_color obj;
    t_color diffuse;
    t_color ambient;
    t_color result;
    
    hit_point = vec3_add(origin, vec3_scale(dir, t));
    
    normal = plane->normal;
    
    if (vec3_dot(dir, normal) > 0)
        normal = vec3_scale(normal, -1.0);
    
    light_dir = vec3_normalize(vec3_sub(scene->light.position, hit_point));
    
    diff = fmax(0.0, vec3_dot(normal, light_dir)) * scene->light.brightness;
    
    obj = plane->color;
    
    diffuse = (t_color){
        (int)(obj.r * diff),
        (int)(obj.g * diff),
        (int)(obj.b * diff)
    };
    
    ambient = (t_color){
        (int)(obj.r * scene->ambient_light.ratio * scene->ambient_light.color.r / 255.0),
        (int)(obj.g * scene->ambient_light.ratio * scene->ambient_light.color.g / 255.0),
        (int)(obj.b * scene->ambient_light.ratio * scene->ambient_light.color.b / 255.0)
    };
    
    result = (t_color){
        fmin(255, ambient.r + diffuse.r),
        fmin(255, ambient.g + diffuse.g),
        fmin(255, ambient.b + diffuse.b)
    };
    
    return (result);
}