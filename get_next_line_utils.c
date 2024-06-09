/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertille <bertille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:00:57 by saberton          #+#    #+#             */
/*   Updated: 2024/06/09 16:40:50 by bertille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int get_next_line_utils(int fd)
{
	int 	i;
	char	buffer[BUFFER_SIZE];

	i = 0;
	while (read(fd, &buffer, BUFFER_SIZE) != 0)
	{
		if (*buffer == '\n') { printf("\n");
			return (i); }
		printf("%c", *buffer);
		i++;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	size_t	len;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * (len + 1));
	if (!join)
		return (NULL);
	i = 0;
	while (*s1 && i < len)
		join[i++] = *s1++;
	while (*s2 && i < len)
		join[i++] = *s2++;
	join[i] = '\n';
	return (join);
}
