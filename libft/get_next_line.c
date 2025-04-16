/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:02:43 by ateca             #+#    #+#             */
/*   Updated: 2024/05/25 13:02:47 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_read_buffer(int fd, char *buffer)
{
	char	*bf;
	int		bytes;

	if (buffer == NULL)
		buffer = ft_calloc(1, sizeof(char));
	bf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!bf)
		return (NULL);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, bf, BUFFER_SIZE);
		if (bytes == -1 || (bytes == 0 && buffer == NULL))
		{
			free(buffer);
			free(bf);
			return (NULL);
		}
		bf[bytes] = '\0';
		buffer = ft_strjoin(buffer, bf);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(bf);
	return (buffer);
}

static char	*ft_get_line(char *buffer)
{
	size_t	len;
	size_t	i;
	char	*line;

	len = 0;
	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[len] && buffer[len] != '\n')
		len++;
	line = malloc((len + 2) * sizeof(char));
	if (!line)
		return (NULL);
	while (i <= len)
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_new_buffer(char	*buffer)
{
	size_t	i;
	size_t	j;
	char	*new_buffer;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = malloc(((ft_strlen(buffer) - i) + 1) * sizeof(char));
	if (!new_buffer)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_read_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_get_line(buffer);
	buffer = ft_new_buffer(buffer);
	return (line);
}
