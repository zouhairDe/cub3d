/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:13:15 by mait-lah          #+#    #+#             */
/*   Updated: 2025/02/09 10:13:45 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	handle_mouse_checks(t_game *game, int map_x, int map_y)
{
	if (map_x < 0 || map_y < 0 || map_x >= game->map.max_cols
		|| map_y >= game->map.rows)
		return (printf("out of bounds\n"));
	if (game->map.map[map_y][map_x] == 'D')
	{
		game->map.map[map_y][map_x] = 'd';
		return (printf("door opened at %d,%d\n", map_x, map_y));
	}
	else if (game->map.map[map_y][map_x] == 'd')
	{
		game->map.map[map_y][map_x] = 'D';
		return (printf("door closed at %d,%d\n", map_x, map_y));
	}
	return (0);
}
