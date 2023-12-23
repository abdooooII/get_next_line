/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouafso <abouafso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 01:26:16 by abouafso          #+#    #+#             */
/*   Updated: 2023/12/23 23:18:55 by abouafso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	{
		result = ft_calloc(1, 1);
	}
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
	while (buffer[i] || buffer[i] != '\n')
		i++;
	if (buffer[i] || buffer[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (free(buffer), free(line), NULL);
	line[i] = '\0';
	i = 0;
	while (buffer[i] || buffer != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] || buffer[i] == '\n')
	{
		i++;
		line[i] = '\n';
	}
	return (line);
}
