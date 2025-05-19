/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:37:28 by ateca             #+#    #+#             */
/*   Updated: 2025/05/07 12:07:31 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include <stdio.h>
# include <math.h>

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
}		t_light;

typedef struct s_sphere
{
	t_vec3	center;
	double	diameter;
	t_color	color;
}		t_sphere;

typedef struct s_plane
{
	t_vec3	point;
	t_vec3	normal;
	t_color	color;
}		t_plane;

typedef struct s_scene
{
	t_ambient_light	ambient_light;
	int				number_ambient_light;
	t_camera		camera;
	int				number_camera;
	t_light			light;
	int				number_light;
	t_sphere		sphere;
	int				number_sphere;
	t_plane			plane;
	int				number_plane;
}		t_scene;

void	read_scene(char *file, t_scene *scene);
void	read_ambient_light(char *line, int fd, t_scene *scene);
void	read_camera(char *line, int fd, t_scene *scene);
void	read_light(char *line, int fd, t_scene *scene);
void	read_sphere(char *line, int fd, t_scene *scene);
void	read_plane(char *line, int fd, t_scene *scene);
void	free_gnl_buffer_and_exit(char *line, int fd);
void	free_tokens(char **tokens);

int		number_tokens(char **tokens);

t_color	read_color(char *line, int fd, char *rgb, char **tokens);

t_vec3	read_position(char *xyz, char *line, int fd, char **tokens);
t_vec3	vec3_normalize(t_vec3 v);

double	vec3_length(t_vec3 v);

#endif
