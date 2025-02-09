/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 06:19:36 by mait-lah          #+#    #+#             */
/*   Updated: 2025/02/09 22:52:57 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	is_heigher(int x, int y)
{
	if (x > y)
		return (1);
	return (-1);
}

void	draw_line(t_game *game, int x1, int y1, t_intPoint end)
{
	t_intPoint	d;
	t_intPoint	s;
	int			err;
	int			e2;

	d.x = abs(end.x - x1);
	d.y = abs(end.y - y1);
	s.x = is_heigher(end.x, x1);
	s.y = is_heigher(end.y, y1);
	err = d.x - d.y;
	while (!(x1 == end.x && y1 == end.y))
	{
		my_mlx_pixel_put(&game->minimap, x1, y1, 0xFF0000);
		e2 = 2 * err;
		if (e2 > -d.y)
		{
			err -= d.y;
			x1 += s.x;
		}
		if (e2 < d.x)
		{
			err += d.x;
			y1 += s.y;
		}
	}
}

void	draw_angle_in_map(t_game *game)
{
	int			line_length;
	t_intPoint	end;

	line_length = 40;
	end.x = CENTER_X + line_length * cos(game->player.dir);
	end.y = CENTER_Y + line_length * sin(game->player.dir);
	draw_line(game, CENTER_X, CENTER_Y, end);
}

void	draw_fov_in_map(t_game *game)
{
	int			line_length;
	t_intPoint	end;

	line_length = 80;
	end.x = CENTER_X + line_length * (cos(game->player.dir - FOV / 2));
	end.y = CENTER_Y + line_length * (sin(game->player.dir - FOV / 2));
	draw_line(game, CENTER_X, CENTER_Y, end);
	end.x = CENTER_X + line_length * (cos(game->player.dir + FOV / 2));
	end.y = CENTER_Y + line_length * (sin(game->player.dir + FOV / 2));
	draw_line(game, CENTER_X, CENTER_Y, end);
}

int	door(t_game *game, double pX, double pY)
{
	if (pX <= 0 || pX >= game->map.max_cols || pY <= 0 || pY >= game->map.rows)
		return (false);
	return (game->map.map[(int)(pY)][(int)(pX)] == 'D');
}
