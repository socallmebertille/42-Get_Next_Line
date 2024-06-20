/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:01:03 by saberton          #+#    #+#             */
/*   Updated: 2024/06/20 14:19:29 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <limits.h>


char	*get_next_line(int fd)
{
	char		*line;
	char		*temp;
	static char	*remains;
	char		*buffer;
	size_t		i;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX - 1)
		return (NULL);
	buffer = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	while (read(fd, buffer, BUFFER_SIZE) > 0)
	{
		if (!remains)
			remains = ft_strdup(buffer);
		else
		{
			temp = remains;
			remains = ft_strjoin(remains, buffer);
			free(temp);
		}
		free(buffer);
		buffer = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
		if (!buffer)
			return (NULL);
	}
	free(buffer);
	if (remains)
	{
		i = 0;
		while (remains[i] != '\0')
		{
			if (remains[i] == '\n')
			{
				line = ft_substr(remains, 0, i + 1);
				temp = remains;
				remains = ft_substr(remains, i + 1, ft_strlen(remains) - i + 1);
				free(temp);
				return (line);
			}
			i++;
		}
		line = ft_strdup(remains);
		free(remains);
	}
	remains = NULL;
	return (line);
}

/*int main(void)
{
	int fd;
	char *str;

	// fd = open("get_next_line.c", O_RDONLY);
	// fd = open("multiple_nlx5", O_RDONLY);
	fd = open("test.txt", O_RDONLY);
	// fd = open("nl", O_RDONLY);
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