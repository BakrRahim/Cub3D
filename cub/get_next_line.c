/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosseili <nosseili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:34:05 by nosseili          #+#    #+#             */
/*   Updated: 2023/11/08 19:52:55 by nosseili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"

int	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	int		i;
	char	*dup;

	i = 0;
	if (!s)
		return (NULL);
	dup = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!dup)
		return (NULL);
	while (s && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(char *str, char c)
{
	int		i;
	int		size;
	char	*ptr;

	i = 0;
	size = ft_strlen(str);
	ptr = malloc(size + 2);
	if (!ptr)
		return (NULL);
	while (str[i])
	{
		ptr[i] = str[i];
		i++;
	}
	if (c == '\n')
	{
		ptr[i] = '\0';
		free(str);
		return (ptr);
	}
	ptr[i] = c;
	ptr[i + 1] = '\0';
	free(str);
	return (ptr);
}

char	*get_next_line(int fd)
{
	char	*s;
	char	buffer;
	int		stock;

	stock = read(fd, &buffer, 1);
	s = ft_strdup("");
	while (stock > 0)
	{
		s = ft_strjoin(s, buffer);
		if (buffer == '\n')
			break ;
		stock = read(fd, &buffer, 1);
	}
	if (stock < 0)
	{
		free(s);
		return (NULL);
	}
	if (stock == 0 && s[0] == '\0')
	{
		free(s);
		return (NULL);
	}
	return (s);
}