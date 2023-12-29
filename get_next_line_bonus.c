/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouafso <abouafso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 23:26:14 by abouafso          #+#    #+#             */
/*   Updated: 2023/12/29 03:39:30 by abouafso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_join_and_free(char *buffer, char *buf)
{
	char	*str;

	str = ft_strjoin(buffer, buf);
	free (buffer);
	return (str);
}

char	*read_file(int fd, char *result)
{
	char	*buffer;
	int		line;

	line = 1;
	if (!result)
		result = ft_calloc(1, 1);
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!result || !buffer)
		return (free(result), free (buffer), NULL);
	while (line)
	{
		line = read(fd, buffer, BUFFER_SIZE);
		if (line == -1)
			return (free(result), free(buffer), NULL);
		buffer[line] = '\0';
		result = ft_join_and_free(result, buffer);
		if (ft_strrchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (result);
}

char	*copy_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] && buffer[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (free(buffer), NULL);
	line[i] = '\0';
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*remove_first_line(char *buffer)
{
	char	*new_buff;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free (buffer);
		return (NULL);
	}
	new_buff = ft_calloc((ft_strlen(buffer) - i + 1), 1);
	if (!new_buff)
		return (free(buffer), NULL);
	i++;
	while (buffer[i])
	{
		new_buff[j] = buffer[i];
		j++;
		i++;
	}
	free (buffer);
	return (new_buff);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > OPEN_MAX)
		return (NULL);
	buffer[fd] = read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = copy_line(buffer[fd]);
	buffer[fd] = remove_first_line(buffer[fd]);
	return (line);
}
