/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:47:16 by ateca             #+#    #+#             */
/*   Updated: 2025/05/20 15:47:17 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	add_object_to_list(t_scene *scene, t_object_type type, void *object)
{
	t_object_list	*new_obj;

	new_obj = malloc(sizeof(t_object_list));
	if (new_obj == NULL)
	{
		perror("Error: malloc failed");
		free(object);
		exit(1);
	}
	new_obj->type = type;
	new_obj->object = object;
	new_obj->next = scene->object_list;
	scene->object_list = new_obj;
}
