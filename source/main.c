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

	if (argc != 2)
	{
		printf("Usage: ./miniRT <scene.rt>\n");
		return (1);
	}
	file = argv[1];
	read_scene(file, &scene);
	printf("Ambient Light:\n");
	printf("  Ratio: %.1f\n", scene.ambient_light.ratio);
	printf("  Color: R=%d, G=%d, B=%d\n", scene.ambient_light.color.r,
		scene.ambient_light.color.g, scene.ambient_light.color.b);
	printf("Light:\n");
	printf("  Position: x=%.1f, y=%.1f, z=%.1f\n", scene.light.position.x,
		scene.light.position.y, scene.light.position.z);
	printf("  Brightness: %.1f\n", scene.light.brightness);
	printf("Camera:\n");
	printf("  Position: x=%.1f, y=%.1f, z=%.1f\n", scene.camera.position.x,
		scene.camera.position.y, scene.camera.position.z);
	printf("  Direction: x=%.1f, y=%.1f, z=%.1f\n", scene.camera.direction.x,
		scene.camera.direction.y, scene.camera.direction.z);
	printf("  FOV: %.1f\n", scene.camera.fov);
	printf("Sphere:\n");
	printf("  Center: x=%.1f, y=%.1f, z=%.1f\n", scene.sphere.center.x,
		scene.sphere.center.y, scene.sphere.center.z);
	printf("  Diameter: %.1f\n", scene.sphere.diameter);
	printf("  Color: R=%d, G=%d, B=%d\n", scene.sphere.color.r,
		scene.sphere.color.g, scene.sphere.color.b);
	return (0);
}
