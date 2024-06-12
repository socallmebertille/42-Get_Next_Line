/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:00:19 by saberton          #+#    #+#             */
/*   Updated: 2024/06/12 16:05:07 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	get_nb_line(int fd)
{
	int		i;
	int		count;
	char	buffer[BUFFER_SIZE + 1];

	count = 0;
	while (read(fd, buffer, BUFFER_SIZE) > 0)
	{
		buffer[BUFFER_SIZE] = '\0';
		i = 0;
		while (buffer[i])
		{
			if (buffer[i] == '\n')
				return (count);
			// printf("%c", buffer[i]);
			i++;
			count++;
		}
	}
	return (0);
}

char    *get_next_line2(int fd)
{
	static char buffer[BUFFER_SIZE + 1];
	char        *line;
	// size_t      bytes_read;
	int			i;

	printf("[nb char] %d ", get_nb_line(fd));
	line = (char *)malloc(sizeof(char) * (get_nb_line(fd) + 1));
	// if (!buffer)
	// 	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	// else
	// 	buffer = (char *)calloc(sizeof(char), BUFFER_SIZE + 1);
	// bytes_read = read(fd, buffer, BUFFER_SIZE);
	//i = 0;
	while (read(fd, buffer, BUFFER_SIZE) > 0)
	{
		buffer[BUFFER_SIZE] = '\0';
		i = 0;
		while (buffer[i])
		{
			if (buffer[i] == '\n')
			{
				if (line == (void *)0)
					line = ft_strdup(ft_substr(buffer, 0, i));
				else
					line = ft_strjoin(line, ft_substr(buffer, 0, i));
			}
			else
			{
				if (line == (void *)0)
					line = ft_strdup(ft_substr(buffer, 0, BUFFER_SIZE));
				else
					line = ft_substr(buffer, 0, BUFFER_SIZE);
			}
			// printf("%c", buffer[i]);
			i++;
		}
	}
	// if (line == (void *)0)
	// 	line = ft_substr(buffer, 0, i);
	// else
	// 	line = ft_substr(buffer, 0, BUFFER_SIZE);
	// buffer = ft_substr(buffer, i + 1, BUFFER_SIZE);
	printf("[line] : %s \n", line);
	return (line);
}
int main(void)
{
	int fd;

	//fd = open("get_next_line.c", O_RDONLY);
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		write(2, "Cannot read file.\n", 18);
		return (1);
	}
	//printf("next_line : %s", get_next_line2(fd));
	for (int i = 0; i < 5; i++)
		printf("%s", get_next_line2(fd));
	close(fd);
	if (close(fd) == -1)
		return (1);
	return (0);
}