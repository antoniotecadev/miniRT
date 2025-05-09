/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:56:56 by ateca             #+#    #+#             */
/*   Updated: 2025/05/09 13:57:03 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof_parse_fraction(const char *str)
{
	double	fraction;
	double	divisor;

	fraction = 0.0;
	divisor = 1.0;
	while (*str >= '0' && *str <= '9')
	{
		fraction = fraction * 10 + (*str - '0');
		divisor = divisor * 10;
		str++;
	}
	return (fraction / divisor);
}

double	ft_atof(const char *str)
{
	int		sign;
	double	result;

	sign = 1;
	result = 0.0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		result += ft_atof_parse_fraction(str);
	}
	return (result * sign);
}
