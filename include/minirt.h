/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:37:28 by ateca             #+#    #+#             */
/*   Updated: 2025/04/16 16:37:29 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include <stdio.h>

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}		t_vec3;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}		t_color;

typedef struct s_ambient_light
{
	double	ratio;
	t_color	color;
}		t_ambient_light;

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	direction;
	double	fov;
}		t_camera;

typedef struct s_light
{
	t_vec3		position;
	double		brightness;
	t_color		color;
}	t_light;

typedef struct s_scene
{
	t_ambient_light	ambient_light;
	int				number_ambient_light;
	t_camera		camera;
	t_light			light;
}		t_scene;

void	parse_scene(char *file, t_scene *scene);
void	parse_ambient_light(char *line, t_scene *scene);

#endif
