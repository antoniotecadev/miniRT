/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:42:34 by ateca             #+#    #+#             */
/*   Updated: 2024/05/15 17:42:39 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_filed(const char *nptr)
{
	int			res;
	int			signal;
	int			i;

	res = 0;
	signal = 1;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			signal = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = ((res * 10) + (nptr[i] - '0'));
		i++;
	}
	return (res * signal);
}

int	ft_atoi(const char *str)
{
	long long int	nbr;
	int				sign;

	nbr = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + *str - '0';
		str++;
		if ((nbr > (unsigned int)INT_MIN && sign == -1)
			|| (nbr > INT_MAX && sign == 1))
		{
			return (INT_MAX);
		}
	}
	return (sign * nbr);
}
