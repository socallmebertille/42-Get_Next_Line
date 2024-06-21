/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:01:03 by saberton          #+#    #+#             */
/*   Updated: 2024/06/21 21:07:17 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <limits.h>

int	get_end_line(char *buffer)
{
	int	i;

	i = 0;
	if (!buffer)
		return (-1);
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*temp;
	static char	*remains;
	char		*buffer;
	int			end;
	int			bytes_read;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX - 1)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = remains;
		remains = ft_strjoin(remains, buffer);
		// printf("remains [%s] de taille [%d]\n", remains, ft_strlen(remains));
		if (temp)
			free(temp);
		end = get_end_line(remains);
		if (end != -1)
		{
			line = ft_substr(remains, 0, end + 1);
			// printf("end line [%zu] line [%s] de taille [%d]\n", end + 1, line, ft_strlen(line));
			temp = remains;
			if (remains[end + 1])
				remains = ft_strjoin(remains + end + 1, "");
			else
				remains = NULL;
			free(temp);
			free(buffer);
			return (line);
		}
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (bytes_read == -1)
	{
		if (remains)
		{
			free(remains);
			remains = NULL;
		}
		return (NULL);
	}
	if (remains)
	{
		end = get_end_line(remains);
		if (end != -1)
		{
			line = ft_substr(remains, 0, end + 1);
			temp = remains;
			if (remains[end + 1])
				remains = ft_strjoin(remains + end + 1, "");
			else
				remains = NULL;
			free(temp);
			return (line);
		}
		line = ft_strjoin(remains, "");
		// printf("end line [%d] line [%s] de taille [%d]\n", end + 1, line, ft_strlen(remains));
		free(remains);
		remains = NULL;
		return (line);
	}
	return (NULL);
}

/*int main(void)
{
	int fd;
	char *str;

	// fd = open("read_error.txt", O_RDONLY);
	// fd = open("nltest", O_RDONLY);
	fd = open("multiple_nl.txt", O_RDONLY);
	if (fd == -1)
	{
		write(2, "Cannot read file.\n", 18);
		return (1);
	}
	while ((str = get_next_line(fd)) != NULL)
	{
		printf("line = %s", str);
		free(str);
	}
	printf("last line = %s", str);
	free(str);
	close(fd);
	if (close(fd) == -1)
		return (1);
	return (0);
}*/