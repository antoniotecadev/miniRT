/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:44:02 by ateca             #+#    #+#             */
/*   Updated: 2025/04/03 16:44:18 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	main(void)
{
	char	*str;

	str = "Hello World! MiniRT\n";
	write(1, str, ft_strlen(str));
	int fd = open("Makefile", O_RDONLY);
	if (fd < 0)
		write(1, "Error\n", 6);
	char *line = get_next_line(fd);
	while (line)
	{
		write(1, line, ft_strlen(line));
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
