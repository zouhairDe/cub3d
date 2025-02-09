/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:46:08 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/09 19:25:12 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	floodfill(t_map *map, int x, int y)
{
	if (x < 0 || y < 0 || x >= map->rows || (size_t)y >= ft_strlen(map->map[x]))
		return ;
	if (map->map[x] == NULL)
		return ;
	if (map->map[x][y] == '1' || map->map[x][y] == '*')
		return ;
	map->map[x][y] = '*';
	floodfill(map, x + 1, y);
	floodfill(map, x - 1, y);
	floodfill(map, x, y + 1);
	floodfill(map, x, y - 1);
}

int	check_chars(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] != '1' && map->map[i][j] != '0'
				&& map->map[i][j] != '2' && map->map[i][j] != 'N'
				&& map->map[i][j] != 'S' && map->map[i][j] != 'E'
				&& map->map[i][j] != 'W' && map->map[i][j] != '\n'
				&& map->map[i][j] != ' ')
				return (printf("Error\nInvalid character in line: %s, Col\
						%d --> '%c'\n", map->map[i], j, map->map[i][j]));
			j++;
		}
		i++;
	}
	return (0);
}

int	start_map_equalization(char **new_map, char **map, int row_count,
	int max_length)
{
	int	i;

	i = -1;
	while (++i < row_count)
	{
		new_map[i] = equalize_map_row(map[i], max_length);
		if (!new_map[i])
		{
			while (--i >= 0)
				free(new_map[i]);
			free(new_map);
			return (-1);
		}
	}
	new_map[row_count] = NULL;
	return (0);
}

char	**equalize_map(char **map, int row_count)
{
	char	**new_map;
	int		max_length;
	int		len;
	int		i;

	if (!map || row_count <= 0)
		return (NULL);
	max_length = 0;
	i = -1;
	while (++i < row_count)
	{
		len = strlen(map[i]);
		if (len > max_length)
			max_length = len;
	}
	new_map = malloc((row_count + 1) * sizeof(char *));
	if (!new_map)
		return (NULL);
	if (start_map_equalization(new_map, map, row_count, max_length) == -1)
		return (NULL);
	i = -1;
	while (++i < row_count)
		free(map[i]);
	return (new_map);
}
