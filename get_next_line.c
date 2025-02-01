/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisingja <sisingja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 21:15:27 by sisingja          #+#    #+#             */
/*   Updated: 2025/02/01 01:31:31 by sisingja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_file(char *temp, int fd, char *buff)
{
	ssize_t	r;
	char	*new_temp;

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
		buff[r] = '\0';
		new_temp = ft_strjoin(temp, buff);
		if (!new_temp)
		{
			free(buff);
			return (NULL);
		}
		temp = new_temp;
	}
	free(buff);
	return (temp);
}

static char	*get_next_line_buffer(char **temp)
{
	char	*line;
	char	*new_temp;
	char	*ptr;

	ptr = *temp;
	while (*ptr && *ptr != '\n')
		ptr++;
	ptr += (*ptr == '\n');
	line = ft_substr(*temp, 0, ptr - *temp);
	if (!line)
	{
		free(*temp);
		return (NULL);
	}
	new_temp = ft_substr(ptr, 0, ft_strlen(ptr));
	free(*temp);
	*temp = new_temp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*temp = NULL;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!temp)
		temp = ft_strdup("");
	if (!temp)
		return (NULL);
	buffer = malloc(sizeof(*buffer) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		free(temp);
		return (NULL);
	}
	temp = read_file(temp, fd, buffer);
	if (!temp || !*temp)
	{
		free(temp);
		temp = NULL;
		return (NULL);
	}
	return (get_next_line_buffer(&temp));
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
