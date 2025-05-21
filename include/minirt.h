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

# include "../minilibx/mlx.h"
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

typedef struct s_cylinder
{
	t_vec3	center;
	t_vec3	axis;
	double	diameter;
	double	height;
	t_color	color;
}		t_cylinder;

typedef enum e_object_type
{
	PLANE,
	SPHERE,
	CYLINDER
}		t_object_type;

typedef struct s_object_list
{
	t_object_type			type;
	void					*object;
	struct s_object_list	*next;
}		t_object_list;

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
	t_cylinder		cylinder;
	int				number_cylinder;
	t_object_list	*object_list;
}		t_scene;

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_scene	scene;
}				t_data;

typedef struct s_ray_var
{
	double	x;
	double	y;
	t_vec3	up;
	t_vec3	right;
	t_vec3	forward;
	t_vec3	up_world;
	t_vec3	direction;
}		t_ray_var;

void	read_scene(char *file, t_scene *scene);
void	add_object_to_list(t_scene *scene, t_object_type type, void *object);

void	ambient_light(char *line, int fd, t_scene *scene);
void	camera(char *line, int fd, t_scene *scene);
void	light(char *line, int fd, t_scene *scene);

void	sphere(char *line, int fd, t_scene *scene);
void	plane(char *line, int fd, t_scene *scene);
void	cylinder(char *line, int fd, t_scene *scene);

void	render_scene(t_scene *scene, t_data *img);

void	free_gnl_buffer_and_exit(char *line, int fd);
void	free_tokens(char **tokens);
void	free_objects(t_object_list *object_list);
void	free_mlx(t_data *img);

int		number_tokens(char **tokens);

int		events_press_esc(int keycode, t_data *img);
int		close_window_x(t_data *img);

t_color	get_color(char *line, int fd, char *rgb, char **tokens);
t_color	ray_trace(t_scene *scene, t_vec3 origin, t_vec3 dir);

t_vec3	vec3_normalize(t_vec3 v);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);

t_vec3	get_position(char *xyz, char *line, int fd, char **tokens);
t_vec3	get_ray_direction(t_camera camera, int i, int j);

double	vec3_length(t_vec3 v);
double	vec3_dot(t_vec3 a, t_vec3 b);
double	intersect_sphere(t_vec3 ray_origin, t_vec3 ray_dir, t_sphere *sphere);

#endif
