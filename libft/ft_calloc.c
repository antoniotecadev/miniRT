/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:44:07 by ateca             #+#    #+#             */
/*   Updated: 2024/05/16 10:44:11 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	area;
	void	*mem_allocated;

	if (size != 0 && nmemb > (size_t) - 1 / size)
		return (NULL);
	area = nmemb * size;
	mem_allocated = malloc(area);
	if (!mem_allocated)
		return (NULL);
	else
		ft_bzero(mem_allocated, area);
	return (mem_allocated);
}
