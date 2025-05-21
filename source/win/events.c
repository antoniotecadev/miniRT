/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:14:03 by ateca             #+#    #+#             */
/*   Updated: 2025/05/21 09:14:07 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	events_press_esc(int keycode, t_data *img)
{
	if (keycode == 65307)
		free_mlx(img);
	return (0);
}

int	close_window_x(t_data *img)
{
	free_mlx(img);
	return (0);
}
