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
	printf("Ambient Light: %d\n", scene.number_ambient_light);
	printf("  Ratio: %.1f\n", scene.ambient_light.ratio);
	printf("  Color: R=%d, G=%d, B=%d\n", scene.ambient_light.color.r,
		scene.ambient_light.color.g, scene.ambient_light.color.b);
	printf("Light: %d\n", scene.number_light);
	printf("  Position: x=%.1f, y=%.1f, z=%.1f\n", scene.light.position.x,
		scene.light.position.y, scene.light.position.z);
	printf("  Brightness: %.1f\n", scene.light.brightness);
	printf("Camera: %d\n", scene.number_camera);
	printf("  Position: x=%.1f, y=%.1f, z=%.1f\n", scene.camera.position.x,
		scene.camera.position.y, scene.camera.position.z);
	printf("  Direction: x=%.1f, y=%.1f, z=%.1f\n", scene.camera.direction.x,
		scene.camera.direction.y, scene.camera.direction.z);
	printf("  FOV: %.1f\n", scene.camera.fov);
	printf("Sphere: %d\n", scene.number_sphere);
	printf("  Center: x=%.1f, y=%.1f, z=%.1f\n", scene.sphere.center.x,
		scene.sphere.center.y, scene.sphere.center.z);
	printf("  Diameter: %.1f\n", scene.sphere.diameter);
	printf("  Color: R=%d, G=%d, B=%d\n", scene.sphere.color.r,
		scene.sphere.color.g, scene.sphere.color.b);
	printf("Plane:  %d\n", scene.number_plane);
	printf("  Point: x=%.1f, y=%.1f, z=%.1f\n", scene.plane.point.x,
		scene.plane.point.y, scene.plane.point.z);
	printf("  Normal: x=%.1f, y=%.1f, z=%.1f\n", scene.plane.normal.x,
		scene.plane.normal.y, scene.plane.normal.z);
	printf("  Color: R=%d, G=%d, B=%d\n", scene.plane.color.r,
		scene.plane.color.g, scene.plane.color.b);
	printf("Cylinder: %d\n", scene.number_cylinder);
	printf("  Center: x=%.1f, y=%.1f, z=%.1f\n", scene.cylinder.center.x,
		scene.cylinder.center.y, scene.cylinder.center.z);
	printf("  Axis: x=%.1f, y=%.1f, z=%.1f\n", scene.cylinder.axis.x,
		scene.cylinder.axis.y, scene.cylinder.axis.z);
	printf("  Diameter: %.1f\n", scene.cylinder.diameter);
	printf("  Height: %.1f\n", scene.cylinder.height);
	printf("  Color: R=%d, G=%d, B=%d\n", scene.cylinder.color.r,
		scene.cylinder.color.g, scene.cylinder.color.b);
	return (0);
}
