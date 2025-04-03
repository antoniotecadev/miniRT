/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:18:42 by ateca             #+#    #+#             */
/*   Updated: 2024/05/14 16:18:45 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*dst;
	const char	*source;

	i = 0;
	dst = (char *)dest;
	source = (const char *)src;
	while (i < n)
	{
		dst[i] = source[i];
		i++;
	}
	return (dest);
}
