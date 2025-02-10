/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 22:46:11 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/10 17:43:21 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d_bonus/includes/cub3d_bonus.h"

void	when_recall(char **buffer, char **line)
{
	if (ft_gnl_strchr(*buffer, '\n'))
	{
		if (*(ft_gnl_strchr(*buffer, '\n') + 1))
		{
			*buffer = ft_trim(*buffer);
			*line = ft_gnl_strjoin(*buffer, NULL);
			if (!**buffer)
			{
				free_ptr(get_game(2, NULL), *buffer);
				*buffer = NULL;
			}
		}
	}
	else
	{
		*line = ft_gnl_strdup(*buffer);
		free_ptr(get_game(2, NULL), *buffer);
		*buffer = NULL;
	}
}

char	*save_line(char **line, char **buffer, int fd)
{
	int	read_bytes;

	while (1)
	{
		if (ft_gnl_strchr(*line, '\n'))
			return (*line);
		read_bytes = read(fd, buffer[fd], 1000);
		if (read_bytes == -1)
			return (NULL);
		if (read_bytes == 0)
			return (free_ptr(get_game(2, NULL), buffer[fd]), buffer[fd] = NULL, *line);
		buffer[fd][read_bytes] = '\0';
		*line = ft_gnl_strjoin(buffer[fd], *line);
	}
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || 1000 <= 0 || 1000 > 2147483647)
		return (NULL);
	if (read(fd, 0, 0) == -1)
		return (free_ptr(get_game(2, NULL), buffer[fd]), buffer[fd] = NULL, NULL);
	line = NULL;
	if (buffer[fd] != NULL)
		when_recall(&buffer[fd], &line);
	if (buffer[fd] == NULL)
	{
		buffer[fd] = g_malloc(get_game(2, NULL), (size_t)1000 + 1);
		if (!buffer[fd])
			return (NULL);
	}
	return (save_line(&line, buffer, fd));
}
