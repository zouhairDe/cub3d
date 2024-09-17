/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 04:48:13 by zouddach          #+#    #+#             */
/*   Updated: 2024/09/17 05:41:11 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"
#include <stdbool.h>
#include <stdio.h>

int	copy_map(t_game *game)
{
	int i;
	int j;

	i = 0;
	game->check_map.map = malloc(sizeof(char *) * game->map.rows);
	if (!game->check_map.map)
		return (1);
	while (i < game->map.rows)
	{
		game->check_map.map[i] = ft_strdup(game->map.map[i]);
		i++;
	}
	game->check_map.rows = game->map.rows;
	game->check_map.cols = game->map.cols;
	return (0);
}

int	ft_find(char *str, char c)
{
	int i;
	
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

int	setPlayer(t_game *game)
{
	int i;
	bool posSet;
	
	i = 0;
	posSet = false;
	while (game->check_map.map[i])//wtf why is this not working
	{
		if (ft_find(game->check_map.map[i], 'N') != -1 ||
			ft_find(game->check_map.map[i], 'S') != -1 ||
			ft_find(game->check_map.map[i], 'E') != -1 ||
			ft_find(game->check_map.map[i], 'W') != -1)
		{
			if (posSet == true)
				return (printf("Error\nMultiple player starting positions\n"));
			game->player.pos.x = i;
			game->player.pos.y = ft_find(game->check_map.map[i], 'N');
			if (ft_find(game->check_map.map[i], 'S') != -1)
				game->player.dir = 180;
			else if (ft_find(game->check_map.map[i], 'E') != -1)
				game->player.dir = 90;
			else if (ft_find(game->check_map.map[i], 'W') != -1)
				game->player.dir = 270;
			else
				game->player.dir = 0;
			posSet = true;
		}
		i++;
	}
	if (!posSet)
		return (printf("Error\nNo player starting position\n"));
	return (0);
}

void	floodfill(t_map *map, int x, int y)
{
	if (x < 0 || y < 0 || x >= map->rows || map->map[x][y] == '1' || map->map[x][y] == ' ')
		return ;
	map->map[x][y] = '*';
	floodfill(map, x + 1, y);
	floodfill(map, x - 1, y);
	floodfill(map, x, y + 1);
	floodfill(map, x, y - 1);
}

int	check_chars(t_map *map)
{
	int i;
	int j;
	
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] != '1' && map->map[i][j] != '0' &&
				map->map[i][j] != '2' && map->map[i][j] != 'N' &&
				map->map[i][j] != 'S' && map->map[i][j] != 'E' &&
				map->map[i][j] != 'W' && map->map[i][j] != '\n' &&
				map->map[i][j] != ' ')
				return (printf("Error\nInvalid character in map %s\nat %d --> %cy\n", map->map[i], j, map->map[i][j]));
			j++;
		}
		i++;
	}
	return (0);
}

int check_map(t_game *game)
{
	if (copy_map(game))
		return (1);
	if (check_chars(&game->check_map))
		return (1);
	//chhad lmlawi
	// if (setPlayer(game))
	// 	return (1);
	// floodfill(&game->check_map, 5, 13);
	// for (int i = 0; i < game->check_map.rows; i++)
	// 	printf("%s\n", game->check_map.map[i]);
	return (0);
}