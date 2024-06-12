/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utilsTH.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnedel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:19:04 by tnedel            #+#    #+#             */
/*   Updated: 2024/06/12 16:10:32 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_lineTH.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	ft_bzero(void *p, size_t n)
{
	char	*s;

	s = (char *)p;
	while (n-- > 0)
		*s++ = '\0';
	return ;
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	size_t	len;
	size_t	i;

	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * (len + 1));
	if (!join)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (*s1 && i < len)
			join[i++] = *s1++;
	}
	while (*s2 && i < len)
		join[i++] = *s2++;
	join[i] = '\0';
	return (join);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	lens;

	i = 0;
	if (!s)
		return (NULL);
	lens = ft_strlen((char *)s);
	if (start >= lens)
	{
		sub = "";
		return (sub);
	}
	if (len > lens - start)
		len = lens - start;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (s[start] != '\0' && i < len && len != 0)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	len;

	len = nmemb * size;
	if (nmemb != 0 && len / nmemb != size)
		return (NULL);
	ptr = malloc(len);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, len);
	return (ptr);
}
