/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_lineTH.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:18:11 by tnedel            #+#    #+#             */
/*   Updated: 2024/06/12 16:10:21 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_lineTH.h"
#include <stdio.h>

char	*read_line(int fd, char *buffer)
{
	int		byte_read;
	int		i;
	char	*tmp;

	tmp = NULL;
	printf("[buff_b]\t: ----------------%s-----------------\n", buffer);
	tmp = ft_strjoin(tmp, buffer);
	printf("[tmp]\t\t: ----------------%s---------------\n", buffer);
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
			return (NULL);
		printf("[buff]\t\t: ----------------%s-----------------\n", buffer);
		//printf("------------[byte_read]\t: %d\n", byte_read);
		i = 0;
		while (buffer[i] && buffer[i] != '\n')
			i++;
		if (!buffer[i])
			tmp = ft_strjoin(tmp, buffer);
		else
		{
			tmp = ft_strjoin(tmp, ft_substr(buffer, 0, i + 1));
			buffer = ft_substr(buffer, i + 1, BUFFER_SIZE - i);
			printf("[buff_f]\t: ----------------%s---------------\n", buffer);
			return (tmp);	
		}
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char				*ret;
	static char	*buffer;

	ret = NULL;
	if (!buffer)
	{
		buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
	}
	ret = read_line(fd, buffer);
	return (ret);
}

int main(void)
{
	int fd;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		write(2, "Cannot read file.\n", 18);
		return (1);
	}
	for (int i = 0; i < 2; i++)
		printf("%s", get_next_line(fd));
	close(fd);
	if (close(fd) == -1)
		return (1);
	return (0);
}


