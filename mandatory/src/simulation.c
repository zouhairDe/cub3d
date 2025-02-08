/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 06:49:38 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/08 13:17:34 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	clean_window(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		j = 0;
		while (j < WINDOW_HEIGHT)
		{
			my_mlx_pixel_put(data, i, j, 0X00CDD0D4);
			j++;
		}
		i++;
	}
}

void	draw_diagonal_lines(t_game *game, int i)
{
	int			j;
	int			k;
	t_intPoint	point1;
	t_intPoint	point2;

	j = -(game->crosshair.thickness / 2) - 1;
	while (++j <= game->crosshair.thickness / 2)
	{
		k = -(game->crosshair.thickness / 2) - 1;
		while (++k <= game->crosshair.thickness / 2)
		{
			point1.x = WIN_CENTER_X + i + j;
			point1.y = WIN_CENTER_Y + i + k;
			if (point1.x >= 0 && point1.x < WINDOW_WIDTH && point1.y >= 0
				&& point1.y < WINDOW_HEIGHT)
				my_mlx_pixel_put(&game->mlx.data, point1.x, point1.y,
					0X00FFFFFF);
			point2.x = WIN_CENTER_X + i + j;
			point2.y = WIN_CENTER_Y - i + k;
			if (point2.x >= 0 && point2.x < WINDOW_WIDTH && point2.y >= 0
				&& point2.y < WINDOW_HEIGHT)
				my_mlx_pixel_put(&game->mlx.data, point2.x, point2.y,
					0X00FFFFFF);
		}
	}
}

void	draw_crosshair(t_game *game)
{
	int	i;

	i = -game->crosshair.size;
	while (i <= game->crosshair.size)
	{
		draw_diagonal_lines(game, i);
		i++;
	}
}

int	simulate(t_game *game)
{
	mlx_clear_window(game->mlx.mlx, game->mlx.win);
	clean_window(&game->mlx.data);
	collor_ceilling(game);
	collor_floor(game);
	cast_rays(game);
	draw_crosshair(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->mlx.data.img, 0,
		0);
	return (0);
}
