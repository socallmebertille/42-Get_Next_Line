/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:01:03 by saberton          #+#    #+#             */
/*   Updated: 2024/06/17 23:41:21 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	char		*line;
	char		*temp;
	static char	*remains;
	char		*buffer;
	// size_t		bytes_read;
	size_t		i;


	line = NULL;
	// if (fd < 0)
	// 	return (line);
	if (remains)
	{
		line = ft_strdup(remains);
		free(remains);
		remains = NULL;
	}
	buffer = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	// buffer[bytes_read] = '\0';
	while (read(fd, buffer, BUFFER_SIZE) > 0)
	{
		// printf("buffer : %s\n", buffer);
		// if (buffer[0] == '\0')
		// 	return (NULL);
		i = 0;
		while (buffer[i] != '\0')
		{
			if (buffer[i] == '\n')
			{
				temp = ft_strdup(line);
				free(line);
				remains = ft_substr(buffer, 0, i + 1);
				line = ft_strjoin(temp, remains);
				free(temp);
				free(remains);
				remains = NULL;
				if (i + 1 < BUFFER_SIZE && buffer[i + 1])
					remains = ft_substr(buffer, i + 1, BUFFER_SIZE - i);
				free(buffer);
				// buffer = NULL;
				return (line);
			}
			i++;
		}
		// if (buffer[0] == '\0')
		// 	return (NULL);
		temp = ft_strdup(line);
		if (line)
			free(line);
		line = ft_strjoin(temp, buffer);
		free(buffer);
		buffer = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
		if (!buffer)
			return (NULL);
		// bytes_read = read(fd, buffer, BUFFER_SIZE);
		// buffer[bytes_read] = '\0';
		free(temp);
	}
	free(buffer);
	return (line);
}

/*int main(void)
{
	int fd;
	// int len = 2;
	char *str;
	// char **line = (char **)malloc(sizeof(char *) * (len + 1));

	// fd = open("get_next_line.c", O_RDONLY);
	fd = open("multiple_nlx5", O_RDONLY);
	// fd = open("test.txt", O_RDONLY);
	// fd = open("nl", O_RDONLY);
	if (fd == -1)
	{
		write(2, "Cannot read file.\n", 18);
		return (1);
	}
	// for (int i = 0; i < len; i++)
	// {
	// 	line[i] = get_next_line(fd);
	// 	printf("%s", line[i]);
	// }
	// for (int i = 0; i < len; i++)
	// 	free(line[i]);
	// free(line);
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