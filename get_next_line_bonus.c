/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:58:11 by mohaben-          #+#    #+#             */
/*   Updated: 2024/11/18 17:19:46 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_fill(int fd, char *saved_chars, char *buffer)
{
	ssize_t	bytes_read;
	char	*tmp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(saved_chars);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		tmp = saved_chars;
		saved_chars = ft_strjoin(tmp, buffer);
		free(tmp);
		if (saved_chars == NULL)
			return (NULL);
		if (ft_strchr(saved_chars, '\n'))
			break ;
	}
	return (saved_chars);
}

char	*ft_extract_line(char *data)
{
	size_t	i;
	char	*line;

	if (data == NULL)
		return (NULL);
	i = 0;
	while (data[i] && data[i] != '\n')
		i++;
	if (data[i] == '\n')
		i++;
	line = ft_substr(data, 0, i);
	return (line);
}

char	*ft_save_chars_left(char *data)
{
	size_t	i;
	char	*chars_left;

	if (data == NULL)
		return (NULL);
	i = 0;
	while (data[i] && data[i] != '\n')
		i++;
	if (data[i] == '\n')
		i++;
	if (data[i] == '\0')
		return (NULL);
	chars_left = ft_substr(data, i, ft_strlen(data) - i);
	return (chars_left);
}

char	*get_next_line(int fd)
{
	static char	*saved_chars[10240];
	char		*buffer;
	char		*line;
	char		*data;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		free(saved_chars[fd]);
		saved_chars[fd] = NULL;
		return (NULL);
	}
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
	{
		free(saved_chars[fd]);
		saved_chars[fd] = NULL;
		return (NULL);
	}
	data = ft_fill(fd, saved_chars[fd], buffer);
	free(buffer);
	line = ft_extract_line(data);
	saved_chars[fd] = ft_save_chars_left(data);
	free(data);
	return (line);
}
