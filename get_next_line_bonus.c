/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knarman <knarman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 22:32:02 by knarman           #+#    #+#             */
/*   Updated: 2024/02/03 07:00:00 by knarman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>

static int	ft_have_newline(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_read_str(char *str)
{
	int		i;
	char	*dst;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	dst = (char *)malloc(sizeof(char) * (i + 2));
	if (!dst)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		dst[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static char	*ft_copy_str(char *buffer, char *buf)
{
	char	*str;

	if (!buffer && buf)
	{
		str = ft_strdup(buf);
		if (!str)
			return (NULL);
		return (str);
	}
	str = ft_strjoin(buffer, buf);
	ft_free(&buffer, 0);
	return (str);
}

static char	*ft_new_static(char *buffer)
{
	size_t	i;
	char	*str;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n')
		i++;
	if (buffer[i + 1] == '\0')
		return (ft_free(&buffer, 0));
	str = ft_substr(buffer, i + 1, ft_strlen(buffer));
	if (!str)
		return (ft_free(&buffer, 0));
	ft_free(&buffer, 0);
	return (str);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	static char	*buffer[4096];
	ssize_t		read_len;
	char		*read_str;

	read_str = 0;
	read_len = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free(&buffer[fd], 0));
	while (read_len > 0)
	{
		read_len = read(fd, buf, BUFFER_SIZE);
		if ((!read_len && !buffer[fd]) || read_len == -1)
			return (ft_free(&buffer[fd], 0));
		buf[read_len] = '\0';
		buffer[fd] = ft_copy_str(buffer[fd], buf);
		if (ft_have_newline(buffer[fd]))
		{
			read_str = ft_read_str(buffer[fd]);
			if (!read_str)
				return (ft_free(&buffer[fd], 0));
			return (buffer[fd] = ft_new_static(buffer[fd]), read_str);
		}
	}
	return (ft_free(&buffer[fd], 1));
}
