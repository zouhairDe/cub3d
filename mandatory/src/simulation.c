/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 06:49:38 by zouddach          #+#    #+#             */
/*   Updated: 2025/01/29 19:41:54 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double normalizeAngle(double angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return angle;
}

void collorCeilling(t_game *game)
{
	int i;
	int j;
	bool	toggle = false;

	i = 0;
	while (i++ < WINDOW_WIDTH)
	{
		j = 0;
		while (j++ < WINDOW_HEIGHT / 2)
		{
			//if (i < MINIMAP_HEIGHT && j < MINIMAP_HEIGHT)
			//	continue ;
			//else
			my_mlx_pixel_put(&game->mlx.data, i, j, game->walls.ceilling);//game->walls.ceilling);
		}
	}
}

void collorFloor(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		j = WINDOW_HEIGHT / 2;
		while (j < WINDOW_HEIGHT)
		{
			my_mlx_pixel_put(&game->mlx.data, i, j, game->walls.floor);// game->walls.floor);
			j++;
		}
		i++;
	}
}



void clean_window(t_data *data)
{
	int i;
	int j;

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

void draw_rayOnMinimap(t_game *game, double rayX, double rayY)
{
	int i;
	int j;
	int pixelX;
	int pixelY;

	pixelX = (int)(rayX * MINIMAP_SCALE);
	pixelY = (int)(rayY * MINIMAP_SCALE);

	if (pixelX >= 0 && pixelX < MINIMAP_WIDTH && pixelY >= 0 && pixelY < MINIMAP_HEIGHT)
		for (i = 0; i < MINIMAP_SCALE; i++)
			for (j = 0; j < MINIMAP_SCALE; j++)
				my_mlx_pixel_put(&game->mlx.data, pixelX + i, pixelY + j, 0x00FF0000);
}

void	draw_diagonal_lines(t_game *game, int i)
{
	int			j;
	int			k;
	t_intPoint	point1;
	t_intPoint	point2;

	j = -(game->crosshair.thickness / 2);
	while (j <= game->crosshair.thickness / 2)
	{
		k = -(game->crosshair.thickness / 2);
		while (k <= game->crosshair.thickness / 2)
		{
			point1.x = win_center_x + i + j;
			point1.y = win_center_y + i + k;
			if (point1.x >= 0 && point1.x < WINDOW_WIDTH && point1.y >= 0 && point1.y < WINDOW_HEIGHT)
				my_mlx_pixel_put(&game->mlx.data, point1.x, point1.y, 0X00FFFFFF);
			point2.x = win_center_x + i + j;
			point2.y = win_center_y - i + k;
			if (point2.x >= 0 && point2.x < WINDOW_WIDTH && point2.y >= 0 && point2.y < WINDOW_HEIGHT)
				my_mlx_pixel_put(&game->mlx.data, point2.x, point2.y, 0X00FFFFFF);
			k++;
		}
		j++;
	}
}

void	draw_crosshair(t_game *game)
{
	int			i;

	i = -game->crosshair.size;
	while (i <= game->crosshair.size)
	{
		draw_diagonal_lines(game, i);
		i++;
	}
}

int simulate(t_game *game)
{
	int i;
	double rayAngle;
	// printGame(*game);//debuging data (appenfing to file)
	mlx_clear_window(game->mlx.mlx, game->mlx.win);
	clean_window(&game->mlx.data);
	collorCeilling(game);
	collorFloor(game);
	castRays(game);
	draw_crosshair(game);
	//drawMap(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->mlx.data.img, 0, 0); //
	//mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->minimap.img, 0, 0);
	return 0;
}
