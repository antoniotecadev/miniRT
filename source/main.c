/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:44:02 by ateca             #+#    #+#             */
/*   Updated: 2025/05/07 12:08:28 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	main(int argc, char **argv)
{
	char	*file;
	t_scene	scene;
	t_data	img;

	if (argc != 2)
	{
		printf("Usage: ./miniRT <scene.rt>\n");
		return (1);
	}
	file = argv[1];
	read_scene(file, &scene);
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, WIDTH, HEIGHT, "miniRT");
	img.img = mlx_new_image(img.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_hook(img.win, 2, 1L << 0, events_press_esc, &img);
	mlx_hook(img.win, 17, 0L, close_window_x, &img);
	t_object_list *current = scene.object_list;
	while (current != NULL)
	{
		if (current->type == SPHERE)
		{
			t_sphere *sphere = (t_sphere *)current->object;
			printf("Sphere - Center: (%.2f, %.2f, %.2f), Diameter: %.2f\n",
			sphere->center.x,
			sphere->center.y,
			sphere->center.z,
			sphere->diameter);
		}
		current = current->next;
	}
	free_objects(scene.object_list);
	mlx_loop(img.mlx);
	return (0);
}
