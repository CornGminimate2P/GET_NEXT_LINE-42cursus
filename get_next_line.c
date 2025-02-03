/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisingja <sisingja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 21:15:27 by sisingja          #+#    #+#             */
/*   Updated: 2025/02/03 19:40:24 by sisingja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_file(char *line, int fd, char *buff)
{
	ssize_t	reads;
	char	*new_line;

	reads = 1;
	while (reads && !ft_strchr(line, '\n'))
	{
		reads = read(fd, buff, BUFFER_SIZE);
		if (reads == -1)
		{
			free(buff);
			free(line);
			return (NULL);
		}
		buff[reads] = '\0';
		new_line = ft_strjoin(line, buff);
		if (!new_line)
		{
			free(buff);
			return (NULL);
		}
		line = new_line;
	}
	free(buff);
	return (line);
}

static char	*line_buffer(char **line)
{
	char	*ret_line;
	char	*new_line;
	char	*ptr;

	ptr = *line;
	while (*ptr && *ptr != '\n')
		ptr++;
	ptr += (*ptr == '\n');
	ret_line = ft_substr(*line, 0, ptr - *line);
	if (!ret_line)
	{
		free(*line);
		return (NULL);
	}
	new_line = ft_substr(ptr, 0, ft_strlen(ptr));
	free(*line);
	*line = new_line;
	return (ret_line);
}

char	*get_next_line(int fd)
{
	static char	*line = NULL;
	char		*buff;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!line)
		line = ft_strdup("");
	if (!line)
		return (NULL);
	buff = malloc(sizeof(*buff) * (BUFFER_SIZE + 1));
	if (!buff)
	{
		free(line);
		return (NULL);
	}
	line = read_file(line, fd, buff);
	if (!line || !*line)
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	return (line_buffer(&line));
}

//#include <stdio.h>
//#include <fcntl.h>

//int	main(int ac, char *av[])
//{
//	int		fd = open("text.txt", O_RDONLY);
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
