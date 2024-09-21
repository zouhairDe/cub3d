/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 06:49:38 by zouddach          #+#    #+#             */
/*   Updated: 2024/09/21 21:34:30 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
			if (i < MINIMAP_HEIGHT && j < MINIMAP_HEIGHT)
				continue ;
			else
				my_mlx_pixel_put(&game->mlx.data, i, j, game->walls.ceilling);// mlx_pixel_put(game->mlx.mlx, game->mlx.win, i, j, game->walls.ceilling);
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
			// mlx_pixel_put(game->mlx.mlx, game->mlx.win, i, j, game->walls.floor);
			my_mlx_pixel_put(&game->mlx.data, i, j, game->walls.floor);
			j++;
		}
		i++;
	}
}

void drawMiniMapBorders(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (i < MINIMAP_WIDTH)
	{
		j = 0;
		while (j < MINIMAP_HEIGHT)
		{
			if (i == 0 || j == 0 || i == MINIMAP_WIDTH - 1 || j == MINIMAP_HEIGHT - 1)
			{
				// mlx_pixel_put(game->mlx.mlx, game->mlx.win, i, j, 0X00FFFFFF);
				// mlx_pixel_put(game->mlx.mlx, game->mlx.win, i + 1, j + 1, 0X00FFFFFF);
				// mlx_pixel_put(game->mlx.mlx, game->mlx.win, i + 2, j + 2, 0X00FFFFFF);
				my_mlx_pixel_put(&game->mlx.data, i, j, 0X00FFFFFF);
				my_mlx_pixel_put(&game->mlx.data, i + 1, j + 1, 0X00FFFFFF);
				my_mlx_pixel_put(&game->mlx.data, i + 2, j + 2, 0X00FFFFFF);
			}
			j++;
		}
		i++;
	}
}

void drawRotatedMap(t_game *game)
{
    t_point P;
    P = (t_point){game->player.y, game->player.x};
    
    int i, j, x, y;
    int centerX = MINIMAP_WIDTH / 2;
    int centerY = MINIMAP_HEIGHT / 2;

    for (i = 0; i < game->map.rows; i++)
    {
        for (j = 0; j < ft_strlen(game->map.map[i]); j++)
        {
            int mapX = centerX + (j - P.x) * MINIMAP_SCALE;
            int mapY = centerY + (i - P.y) * MINIMAP_SCALE;

            if (mapX < 0 || mapY < 0 || mapX >= MINIMAP_WIDTH || mapY >= MINIMAP_HEIGHT)
                continue;

            if (game->map.map[i][j] == '1')
            {
                for (x = 0; x < MINIMAP_SCALE; x++)
                {
                    for (y = 0; y < MINIMAP_SCALE; y++)
                    {
                        int pixelX = mapX + x;
                        int pixelY = mapY + y;
                        if (pixelX >= 0 && pixelX < MINIMAP_WIDTH && pixelY >= 0 && pixelY < MINIMAP_HEIGHT)
                        {
                            // mlx_pixel_put(game->mlx.mlx, game->mlx.win, pixelX, pixelY, 0X00FFFFFF);
							my_mlx_pixel_put(&game->mlx.data, pixelX, pixelY, 0X00FFFFFF);
                        }
                    }
                }
            }
        }
    }
}



void centerPlayerInMap(t_game *game)
{
	int i;
	int j;
	int centerX = MINIMAP_WIDTH / 2;
	int centerY = MINIMAP_HEIGHT / 2;

	int height = 2 * 4;
	int halfBase = 3;

	for (i = 0; i < height; i++)
	{
		for (j = -i; j <= i; j++)
		{
			// mlx_pixel_put(game->mlx.mlx, game->mlx.win, centerX + j, centerY + i, 0xFF0000);
			my_mlx_pixel_put(&game->mlx.data, centerX + j, centerY + i, 0X00FF0000);
		}
	}
}

void drawMap(t_game *game)
{
	drawMiniMapBorders(game);
	drawRotatedMap(game);
	centerPlayerInMap(game);
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
			my_mlx_pixel_put(data, i, j, 0);
			j++;
		}
		i++;
	}
}

int simulate(t_game *game)
{
	int i;
	double rayAngle;
	t_ray ray;

	mlx_clear_window(game->mlx.mlx, game->mlx.win);
	clean_window(&game->mlx.data);

	collorCeilling(game);
	collorFloor(game);
	drawMap(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->mlx.data.img, 0, 0);
	// cast_ray(game, &ray);
	return 0;
}
