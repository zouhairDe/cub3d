/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 06:19:36 by mait-lah          #+#    #+#             */
/*   Updated: 2025/02/09 06:27:39 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	draw_line(t_game *game, int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	sx = (x1 < x2) ? 1 : -1;
	sy = (y1 < y2) ? 1 : -1;
	err = dx - dy;
	while (1)
	{
		my_mlx_pixel_put(&game->minimap, x1, y1, 0xFF0000);
		if (x1 == x2 && y1 == y2)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}

void	draw_angle_in_map(t_game *game)
{
	int	line_length;
	int	end_x;
	int	end_y;

	line_length = 40;
	end_x = CENTER_X + line_length * cos(game->player.dir);
	end_y = CENTER_Y + line_length * sin(game->player.dir);
	draw_line(game, CENTER_X, CENTER_Y, end_x, end_y);
}

void	draw_fov_in_map(t_game *game)
{
	int	line_length;
	int	end_x;
	int	end_y;

	line_length = 80;
	end_x = CENTER_X + line_length * (cos(game->player.dir - FOV / 2));
	end_y = CENTER_Y + line_length * (sin(game->player.dir - FOV / 2));
	draw_line(game, CENTER_X, CENTER_Y, end_x, end_y);
	end_x = CENTER_X + line_length * (cos(game->player.dir + FOV / 2));
	end_y = CENTER_Y + line_length * (sin(game->player.dir + FOV / 2));
	draw_line(game, CENTER_X, CENTER_Y, end_x, end_y);
}

int	door(t_game *game, double pX, double pY, t_ray *ray)
{
	if (pX <= 0 || pX >= game->map.max_cols || pY <= 0 || pY >= game->map.rows)
		return (false);
	return (game->map.map[(int)(pY)][(int)(pX)] == 'D');
}
