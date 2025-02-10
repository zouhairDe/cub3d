/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:46:08 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/10 21:41:41 by mait-lah         ###   ########.fr       */
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
				free_ptr(get_game(2, NULL), new_map[i]);
			free_ptr(get_game(2, NULL), new_map);
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
	new_map = g_malloc(get_game(2, NULL), (row_count + 1) * sizeof(char *));
	if (!new_map)
		return (NULL);
	if (start_map_equalization(new_map, map, row_count, max_length) == -1)
		return (NULL);
	i = -1;
	while (++i < row_count)
		free_ptr(get_game(2, NULL), map[i]);
	return (new_map);
}

int	ft_path(char *path, t_game *game)
{
	int	dot;

	dot = path - ft_strrchr(path, '.');
	if (dot == 0 || !ft_strncmp(&path[dot], ".cub", 4))
		return (printf("Error\nInvalid file extension\n"));
	game->map.fd = open(path, O_RDONLY);
	if (game->map.fd == -1)
		return (printf("Error\nFile not found\n"));
	return (0);
}
