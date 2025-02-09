/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check3_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:05:39 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/09 22:54:28 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	copy_map(t_game *game)
{
	int	i;

	i = 0;
	game->check_map.map = g_malloc(game, sizeof(char *) * game->map.rows);
	if (!game->check_map.map)
		return (1);
	while (i < game->map.rows)
	{
		game->check_map.map[i] = ft_strdup(game->map.map[i]);
		i++;
	}
	game->check_map.rows = game->map.rows;
	game->check_map.max_cols = game->map.max_cols;
	return (0);
}

int	ft_find(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (str[i] == c)
		return (i);
	return (-1);
}

int	set_player(t_game *game)
{
	int		i;
	bool	pos_set;

	i = 0;
	pos_set = false;
	while (i < game->check_map.rows)
	{
		if (ft_find(game->check_map.map[i], 'N') != -1
			|| ft_find(game->check_map.map[i], 'S') != -1
			|| ft_find(game->check_map.map[i], 'E') != -1
			|| ft_find(game->check_map.map[i], 'W') != -1)
		{
			if (pos_set == true)
				return (printf("Error\nMultiple player starting positions\n"));
			put_player(game, i);
			pos_set = true;
		}
		i++;
	}
	if (!pos_set)
		return (printf("Error\nNo player starting position\n"));
	return (0);
}

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
				&& map->map[i][j] != ' ' && map->map[i][j] != 'D')
				return (printf("Error\nInvalid character in map %s\nat %d -->\
						%c\n", map->map[i], j, map->map[i][j]));
			j++;
		}
		i++;
	}
	return (0);
}
