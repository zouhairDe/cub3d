/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 06:49:38 by zouddach          #+#    #+#             */
/*   Updated: 2025/01/22 19:05:33 by mait-lah         ###   ########.fr       */
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
			//if (i < MINIMAP_HEIGHT && j < MINIMAP_HEIGHT)
			//	continue ;
			//else
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
			else
			{
				my_mlx_pixel_put(&game->mlx.data, i, j, 0X00000000); // background
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

			for (int a =0 ;a < MINIMAP_SCALE;a++) // remove later Grid.
			{
				my_mlx_pixel_put(&game->mlx.data, screenX+a, screenY, 0Xe5e5e5);
				my_mlx_pixel_put(&game->mlx.data, screenX, screenY+a, 0Xe5e5e5);
			}
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

void	draw_diagonal_lines(t_game *game, int center_x, 
			int center_y, int i)
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
			point1.x = center_x + i + j;
			point1.y = center_y + i + k;
			if (point1.x >= 0 && point1.x < WINDOW_WIDTH && point1.y >= 0 && point1.y < WINDOW_HEIGHT)
				my_mlx_pixel_put(&game->mlx.data, point1.x, point1.y, 0X00FFFFFF);
			point2.x = center_x + i + j;
			point2.y = center_y - i + k;
			if (point2.x >= 0 && point2.x < WINDOW_WIDTH && point2.y >= 0 && point2.y < WINDOW_HEIGHT)
				my_mlx_pixel_put(&game->mlx.data, point2.x, point2.y, 0X00FFFFFF);
			k++;
		}
		j++;
	}
}

void	draw_crosshair(t_game *game)
{
	int			center_x;
	int			center_y;
	int			i;

	center_x = WINDOW_WIDTH / 2;
	center_y = WINDOW_HEIGHT / 2;
	i = -game->crosshair.size;
	while (i <= game->crosshair.size)
	{
		draw_diagonal_lines(game, center_x, center_y, i);
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
	drawMap(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->mlx.data.img, 0, 0);
	return 0;
}
