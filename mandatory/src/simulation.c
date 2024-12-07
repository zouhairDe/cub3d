/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 06:49:38 by zouddach          #+#    #+#             */
/*   Updated: 2024/11/25 20:35:35 by mait-lah         ###   ########.fr       */
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
				my_mlx_pixel_put(&game->mlx.data, i, j, 0x00F3FF);//game->walls.ceilling);
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
			my_mlx_pixel_put(&game->mlx.data, i, j, 0X5b3207 );// game->walls.floor);
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
				my_mlx_pixel_put(&game->mlx.data, i, j, 0X00FFFFFF);
				my_mlx_pixel_put(&game->mlx.data, i + 1, j + 1, 0X00FFFFFF);
				my_mlx_pixel_put(&game->mlx.data, i + 2, j + 2, 0X00FFFFFF);
			}
			j++;
		}
		i++;
	}
}

void rotatePoint(double *x, double *y, double angle) {
    double oldX = *x;
    double oldY = *y;
    *x = oldX * cos(angle) - oldY * sin(angle);
    *y = oldX * sin(angle) + oldY * cos(angle);
}

void drawRotatedMap(t_game *game)
{
    t_point P = {game->player.y, game->player.x};
    int centerX = MINIMAP_WIDTH / 2;
    int centerY = MINIMAP_HEIGHT / 2;
    double rotationAngle = game->player.dir;

    for (int i = 0; i < game->map.rows; i++)
    {
        for (int j = 0; j < ft_strlen(game->map.map[i]); j++)
        {
            double mapX = (j - P.x) * MINIMAP_SCALE;
            double mapY = (i - P.y) * MINIMAP_SCALE;
            int screenX = centerX + (int)mapX;
            int screenY = centerY + (int)mapY;

            if (screenX < 0 || screenY < 0 || screenX >= MINIMAP_WIDTH || screenY >= MINIMAP_HEIGHT)
                continue;

            if (game->map.map[i][j] == '1')
            {
                for (int x = 0; x < MINIMAP_SCALE; x++)
                {
                    for (int y = 0; y < MINIMAP_SCALE; y++)
                    {
                        int pixelX = screenX + x;
                        int pixelY = screenY + y;
                        if (pixelX >= 0 && pixelX < MINIMAP_WIDTH && pixelY >= 0 && pixelY < MINIMAP_HEIGHT)
                            my_mlx_pixel_put(&game->mlx.data, pixelX, pixelY, 0X0000FFFF);
                    }
                }
            }
        }
    }
}

void centerPlayerInMap(t_game *game)
{
    int centerX = MINIMAP_WIDTH / 2;
    int centerY = MINIMAP_HEIGHT / 2;
    int radius = 4;

    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            if (x*x + y*y <= radius*radius)
            {
                int pixelX = centerX + x;
                int pixelY = centerY + y;
                
                if (pixelX >= 0 && pixelX < MINIMAP_WIDTH && 
                    pixelY >= 0 && pixelY < MINIMAP_HEIGHT)
                {
                    my_mlx_pixel_put(&game->mlx.data, pixelX, pixelY, 0X00FF0000);
                }
            }
        }
    }
}

void drawMap(t_game *game)
{
	drawMiniMapBorders(game);
	drawRotatedMap(game);
	centerPlayerInMap(game);
	drawAngleInMap(game); // done
	drawFovInMap(game);
	castRays(game);
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


int simulate(t_game *game)
{
	int i;
	double rayAngle;

	mlx_clear_window(game->mlx.mlx, game->mlx.win);
	clean_window(&game->mlx.data);

	collorCeilling(game);
	collorFloor(game);
	drawMap(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->mlx.data.img, 0, 0);
	return 0;
}
