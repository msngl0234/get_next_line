/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul < msengul@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:52:58 by msengul           #+#    #+#             */
/*   Updated: 2024/12/09 12:18:30 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char	*ft_get_new_remainder(char *remainder)
{
	char	*new_line;
	int		i;
	int		j;

	i = ft_count_newline(remainder);
	if (!remainder[i] && remainder)
	{
		free(remainder);
		return (NULL);
	}
	new_line = malloc(ft_strlen(remainder) - i + 1);
	if (!new_line)
	{
		free(remainder);
		return (NULL);
	}
	i++;
	j = 0;
	while (remainder[i])
		new_line[j++] = remainder[i++];
	new_line[j] = '\0';
	free(remainder);
	return (new_line);
}

char	*ft_get_line(char *remainder)
{
	char	*line;
	int		j;

	j = 0;
	if (!remainder[j])
		return (NULL);
	if (ft_strchr(remainder, '\n'))
		line = malloc(ft_count_newline(remainder) + 2);
	else
		line = malloc(ft_count_newline(remainder) + 1);
	if (!line)
		return (free(remainder), NULL);
	j = -1;
	while (remainder[++j] != '\n' && remainder[j] != '\0')
		line[j] = remainder[j];
	if (remainder[j] == '\n')
	{
		line[j] = remainder[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*ft_get_remainder(int fd, char *remainder)
{
	int		read_len;
	char	*temp;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
	{
		free(remainder);
		return (NULL);
	}
	read_len = 1907;
	while (read_len != 0 && !ft_check_newline(remainder))
	{
		read_len = read(fd, temp, BUFFER_SIZE);
		if (read_len == -1)
		{
			free(remainder);
			free(temp);
			return (NULL);
		}
		temp[read_len] = '\0';
		remainder = ft_strjoin(remainder, temp);
	}
	free(temp);
	return (remainder);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*remainder;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(remainder);
		return (NULL);
	}
	remainder = ft_get_remainder(fd, remainder);
	if (!remainder)
		return (NULL);
	line = ft_get_line(remainder);
	remainder = ft_get_new_remainder(remainder);
	return (line);
}
