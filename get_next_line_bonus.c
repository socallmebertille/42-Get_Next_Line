/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:46:28 by saberton          #+#    #+#             */
/*   Updated: 2024/06/24 14:52:26 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	get_end_line(char *remains)
{
	int	i;

	i = 0;
	if (!remains)
		return (-1);
	while (remains[i])
	{
		if (remains[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*get_line(char **remains, int end, int bytes_read)
{
	char	*line;
	char	*temp;

	if (end != -1)
	{
		line = ft_substr(*remains, 0, end + 1);
		temp = *remains;
		*remains = ft_strjoin("", *remains + end + 1);
		if (!*remains && temp[end + 1])
		{
			free(temp);
			return (NULL);
		}
		free(temp);
		return (line);
	}
	if (bytes_read == 0)
	{
		line = ft_strjoin("", *remains);
		free(*remains);
		*remains = NULL;
		return (line);
	}
	return (NULL);
}

static char	*get_remains(char **remains, char *buffer, int bytes_read)
{
	int		end;
	char	*temp;
	char	*line;

	if (*remains && bytes_read == -1)
	{
		free(*remains);
		*remains = NULL;
		return (NULL);
	}
	buffer[bytes_read] = '\0';
	line = NULL;
	temp = *remains;
	*remains = ft_strjoin(*remains, buffer);
	free(temp);
	end = get_end_line(*remains);
	if (end != -1 || bytes_read == 0)
		line = get_line(remains, end, bytes_read);
	if (line)
	{
		free(buffer);
		return (line);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	int			bytes_read;
	char		*line;
	char		*buffer;
	static char	*remains[FD_MAX] = {NULL};

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX - 1)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		line = get_remains(&remains[fd], buffer, bytes_read);
		if (line)
			return (line);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (remains[fd] && bytes_read == -1)
		return (get_remains(&remains[fd], NULL, bytes_read));
	if (remains[fd] && bytes_read != -1)
		return (get_line(&remains[fd], get_end_line(remains[fd]), bytes_read));
	return (NULL);
}

/*#include <stdio.h>

int main(void)
{
	int		line = 0;
	int		fd1;
	int		fd2;
	int		fd3;
	char	*str;

	fd1 = open("get_next_line.h", O_RDONLY);
	fd2 = open("get_next_line_utils.c", O_RDONLY);
	fd3 = open("get_next_line.c", O_RDONLY);
	if (fd1 == -1 || fd2 == -1 || fd3 == -1)
	{
		printf("Cannot read file.\n");
		return (1);
	}
	while (line <= 5)
	{
		str = get_next_line(fd1);
		printf("%s\n", str);
		str = get_next_line(fd2);
		printf("%s\n", str);
		str = get_next_line(fd3);
		printf("%s\n", str);
		line++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	if (close(fd1) == -1 || close(fd2) == -1 || close(fd3) == -1)
		return (1);
	return (0);
}*/