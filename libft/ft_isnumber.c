/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:40:22 by ateca             #+#    #+#             */
/*   Updated: 2025/01/27 11:40:23 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnumber(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && (str[i + 1] >= '0' && str[i + 1] <= '9'))
		i = 1;
	while (str[i] != '\0' && str[i] != '\n' && !ft_isspace(str[i]))
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
