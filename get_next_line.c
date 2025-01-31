/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisingja <sisingja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 21:15:27 by sisingja          #+#    #+#             */
/*   Updated: 2025/01/31 22:02:15 by sisingja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_next_buffer(char **temp)
{
	char	*line;
	char	*ptr;

	ptr = *temp;
	while (*ptr && *ptr != '\n')
		++ptr;
	ptr += (*ptr == '\n');
	line = ft_substr(*temp, 0, (size_t)(ptr - *temp));
	if (!line)
	{
		free(*temp);
		return (NULL);
	}
	ptr = ft_substr(ptr, 0, ft_strlen(ptr));
	free(*temp);
	*temp = ptr;
	return (line);
}

static char	*read_file(char *temp, int fd, char *buff)
{
	ssize_t	r;

	r = 1;
	while (r && !ft_strchr(temp, '\n'))
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (r == -1)
		{
			free(buff);
			free(temp);
			return (NULL);
		}
		buff[r] = 0;
		temp = ft_strjoin(temp, buff);
		if (!temp)
		{
			free(buff);
			return (NULL);
		}
	}
	free(buff);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*temp[FD_MAX];
	char		*buff;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!temp[fd])
		temp[fd] = ft_strdup("");
	if (!temp[fd])
		return (NULL);
	buff = malloc(sizeof(*buff) * (BUFFER_SIZE + 1));
	if (!buff)
	{
		free(temp[fd]);
		return (NULL);
	}
	temp[fd] = read_file(temp[fd], fd, buff);
	if (!temp[fd])
		return (NULL);
	if (!*temp[fd])
	{#include <stdio.h>

		free(temp[fd]);
		temp[fd] = NULL;
		return (NULL);
	}
	return (ft_next_buffer(&temp[fd]));
}

//int	main(int ac, char *av[])
//{
//	int		fd = open(av[1], O_RDONLY);
//	char	*line;

//	while (1)
//	{
//		line = get_next_line(fd);
//		if (!line)
//			break ;
//		printf("%s", line);
//		free(line);
//	}
//	close(fd);
//	return (0);
//}
