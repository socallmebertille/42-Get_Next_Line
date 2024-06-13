/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:01:03 by saberton          #+#    #+#             */
/*   Updated: 2024/06/13 15:31:03 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	char		*temp;
	static char	*current;
	char		buffer[BUFFER_SIZE + 1];
	size_t		i;
	size_t		bytes_read;

	temp = ft_strdup("");
	if (current)
		temp = ft_strjoin(temp, current);
	else
	{
		current = ft_strdup("");
		temp = ft_strjoin(temp, current);
	}
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		i = 0;
		while (buffer[i])
		{
			if (buffer[i] == '\n')
			{
				temp = ft_strjoin(temp, ft_substr(buffer, 0, i + 1));
				current = ft_substr(buffer, i + 1, BUFFER_SIZE - i);
				return (temp);
			}
			i++;
		}
		temp = ft_strjoin(temp, buffer);
		//current = NULL;
	}
	if (bytes_read == 0 || current != NULL)
	{
		current = NULL;
		temp = ft_strjoin(temp, current);
	}
	return (temp);
}

int main(void)
{
	int fd;

	// fd = open("get_next_line.c", O_RDONLY);
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		write(2, "Cannot read file.\n", 18);
		return (1);
	}
	for (int i = 0; i < 5; i++)
	{
		printf("%s", get_next_line(fd));
		//free(get_next_line(fd));
	}
	close(fd);
	if (close(fd) == -1)
		return (1);
	return (0);
}
