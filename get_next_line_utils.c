/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:00:57 by saberton          #+#    #+#             */
/*   Updated: 2024/06/06 21:07:30 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int get_next_line_utils(int fd)
{
	int 	count;
	int 	i;
	char	*buffer;

	i = 0;
	count = 0;
	buffer = (char *)malloc(sizeof(char) * 1);
	while (read(fd, buffer, BUFFER_SIZE) != 0)
	{
		if (read(fd, buffer, BUFFER_SIZE) == -1)
			return (0);
		if (fd == '\n')
			return (i++);
		i++;
	}
	return (0);
}