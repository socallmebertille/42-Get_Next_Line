/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:01:03 by saberton          #+#    #+#             */
/*   Updated: 2024/06/06 22:25:51 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	char    *str;
	char	*buffer;
	int     i;
	int     len;

	i = 0;
	len = get_next_line_utils(fd);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (len == 0 || !buffer)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (len + 1));
	while (read(fd, buffer, BUFFER_SIZE) != 0)
	{
		if (read(fd, buffer, BUFFER_SIZE) == -1)
			return (NULL);
		if (fd == '\n')
		{
			str[i++] = '\n';
			return (str);
		}
		str[i++] = fd;
	}
	return (str);
}

#include <stdio.h>
int main(void)
{
	int fd;

	fd = open("get_next_line.c", O_RDONLY);
	if (fd == -1)
	{
		write(2, "Cannot read file.\n", 18);
		return (1);
	}
	while (get_next_line(fd))
		printf("%s", get_next_line(fd));
	close(fd);
	if (close(fd) == -1)
		return (1);
	return (0);
}
