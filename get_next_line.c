/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertille <bertille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:01:03 by saberton          #+#    #+#             */
/*   Updated: 2024/06/09 16:53:45 by bertille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char *get_next_line(int fd)
{
	static char    *str;
	char			*buffer;
	int   			i;
	int   			len;

	i = 0;
	len = get_next_line_utils(fd);
	//printf("%d\n", len);
	if (len == 0)
		return (NULL);
	if (!str)
		str = (char *)malloc(sizeof(char) * (len + 1));
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str || !buffer)
		return (NULL);
	while (read(fd, &buffer, BUFFER_SIZE) != 0)
	{
		if (read(fd, &buffer, BUFFER_SIZE) == -1)
			return (NULL);
		if (i >= BUFFER_SIZE)
		{
			str = ft_strjoin(str, buffer);
			//printf("%s\n", str);
			//printf("%s\n", buffer);
			if (!str)
				return (NULL);
			buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		}
		if (buffer[i] == '\n')
		{
			str = ft_strjoin(str, buffer);
			if (!str)
				return (NULL);
			return (str);
		}
		i++;
		//*buffer++;
		//printf("%c", str[i]);
		//printf("%c\n", *buffer);
	}
	return (str);
}

int main(void)
{
	int fd;

	fd = open("get_next_line.c", O_RDONLY);
	if (fd == -1)
	{
		write(2, "Cannot read file.\n", 18);
		return (1);
	}
	printf("%s", get_next_line(fd));
	//while (get_next_line(fd))
	//	printf("%s", get_next_line(fd));
	close(fd);
	if (close(fd) == -1)
		return (1);
	return (0);
}
