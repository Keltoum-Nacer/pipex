/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knacer <knacer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:14:02 by knacer            #+#    #+#             */
/*   Updated: 2024/03/22 13:23:07 by knacer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_bytes(int fd, char *line)
{
	char	*str;
	ssize_t	nb;

	str = (char *)malloc(sizeof(char) * (size_t)(BUFFER_SIZE + 1));
	if (!str)
		return (NULL);
	nb = 1;
	while (!(ft_strchr(line, '\n')) && nb != 0)
	{
		nb = read(fd, str, BUFFER_SIZE);
		if (nb == -1)
		{
			free(line);
			free(str);
			return (NULL);
		}
		str[nb] = '\0';
		line = ft_strjoin(line, str);
	}
	free(str);
	return (line);
}

char	*read_line(char *buffer)
{
	char	*save;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	save = (char *)malloc(sizeof(char) * (i + 2));
	if (!save)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		save[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		save[i] = buffer[i];
		i++;
	}
	save[i] = '\0';
	return (save);
}

char	*save_bytes(char *buffer)
{
	char	*b_save;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	b_save = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!b_save)
		return (NULL);
	i++;
	while (buffer[i] != '\0')
		b_save[j++] = buffer[i++];
	b_save[j] = '\0';
	free(buffer);
	return (b_save);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = read_bytes(fd, buffer);
	if (!buffer)
		return (NULL);
	line = read_line(buffer);
	buffer = save_bytes(buffer);
	return (line);
}
