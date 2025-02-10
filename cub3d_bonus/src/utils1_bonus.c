/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 04:45:13 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/10 21:47:04 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

char	*ft_replace(char *str, char chr, char *news)
{
	int		i;
	int		c;
	char	*res;
	char	*original_str;

	if (!str)
		return (NULL);
	c = count_char(str, chr);
	if (c == 0)
		return (str);
	i = 0;
	res = g_malloc(get_game(2, 0), ft_strlen(str) + (ft_strlen(news) * c) + 1);
	if (!res)
		return (NULL);
	original_str = str;
	while (*str)
	{
		if (*str == chr)
			(ft_strlcpy(&res[i], news, ft_strlen(news) + 1),
				i += ft_strlen(news));
		else
			res[i++] = *str;
		str++;
	}
	return (res[i] = '\0', free_ptr(get_game(2, NULL), original_str), res);
}

int	dump_spaces(char **line)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
	if (**line == '\0')
		return (1);
	return (0);
}

int	check_map_boundaries(t_map *map, int i, int j, int len)

{
	if (i == 0 || i == map->rows - 1 || j == 0 || j == len - 1)
		return (printf("Error\nMap not properly enclosed\n"));
	if (i > 0 && ((size_t)j >= ft_strlen(map->map[i - 1])
			|| map->map[i - 1][j] == ' '))
		return (printf("Error\nMap has invalid gap above\n"));
	if (i < map->rows - 1 && ((size_t)j >= ft_strlen(map->map[i + 1])
			|| map->map[i + 1][j] == ' '))
		return (printf("Error\nMap has invalid gap below\n"));
	if (j > 0 && map->map[i][j - 1] == ' ')
		return (printf("Error\nMap has invalid gap to the left\n"));
	if (j < len - 1 && map->map[i][j + 1] == ' ')
		return (printf("Error\nMap has invalid gap to the right\n"));
	return (0);
}

int	check_map_border(t_map *map)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		len = ft_strlen(map->map[i]);
		while (++j < len)
		{
			if (map->map[i][j] == '0' || map->map[i][j] == 'N'
				|| map->map[i][j] == 'S' || map->map[i][j] == 'E'
				|| map->map[i][j] == 'W')
			{
				if (check_map_boundaries(map, i, j, len))
					return (free_all(1, get_game(2, NULL)->gc), -1);
			}
		}
	}
	return (0);
}

int	ft_line_value(char *line, char **value)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	line += 2;
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	*value = ft_strdup(line);
	return (*value == NULL);
}
