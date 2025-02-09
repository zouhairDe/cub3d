/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 04:48:13 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/09 19:20:20 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdlib.h>

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

int	check_map(t_game *game)
{
	if (copy_map(game))
		return (1);
	game->map.map = equalize_map(game->map.map, game->map.rows);
	if (!game->map.map)
		return (1);
	if (check_chars(&game->check_map))
		return (1);
	if (check_map_border(&game->check_map))
		return (1);
	if (set_player(game))
		return (1);
	floodfill(&game->check_map, 5, 13);
	if (not_surrounded(&game->check_map))
		return (1);
	if (convert_to_hex(game))
		return (1);
	if (validate_elements(game))
		return (1);
	if (game->map.no == NULL || game->map.so == NULL || game->map.we == NULL
		|| game->map.ea == NULL)
		return (printf("Error\nMissing texture path\n"));
	if (set_textures(game))
		return (1);
	return (0);
}
