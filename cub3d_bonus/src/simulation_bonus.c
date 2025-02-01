/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 06:49:38 by zouddach          #+#    #+#             */
/*   Updated: 2025/01/29 19:36:36 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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
void drawRotatedMap(t_game *game)
{
   t_point P = {game->player.y, game->player.x};
   double rotationAngle = game->player.dir;

   for (int i = 0; i < game->map.rows; i++)
   {
		int col = ft_strlen(game->map.map[i]);
       for (int j = 0; j < col; j++)
       {
           double mapX = (j - P.x) * MINIMAP_SCALE;
           double mapY = (i - P.y) * MINIMAP_SCALE;
           int screenX = center_x + (int)mapX;
           int screenY = center_y + (int)mapY;
			
           if (game->map.map[i][j] == '1')
           {
				for (int x = 0; x < MINIMAP_SCALE; x++)
				{
					for (int y = 0; y < MINIMAP_SCALE; y++)
					{
						int pixelX = screenX + x;
						int pixelY = screenY + y;
						if (pixelX >= 0 && pixelX < MINIMAP_WIDTH && pixelY >= 0 && pixelY < MINIMAP_HEIGHT)
						{
							int tx = (pixelX-screenX) % (WALL_SIZE/2);
							int ty = (pixelY-screenY) % (WALL_SIZE/2);
							unsigned int color = ((unsigned int *)game->walls.wt.addr)[ty * (WALL_SIZE/2) + tx];
							my_mlx_pixel_put(&game->minimap, pixelX, pixelY, color);
						}
					}
				}
			}
			
       }
   }
}

void centerPlayerInMap(t_game *game)
{
   int radius = 4;

   for (int y = -radius; y <= radius; y++)
   {
       for (int x = -radius; x <= radius; x++)
       {
           if (x*x + y*y <= radius*radius)
           {
               int pixelX = center_x + x;
               int pixelY = center_y + y;
				
               if (pixelX >= 0 && pixelX < MINIMAP_WIDTH && 
                   pixelY >= 0 && pixelY < MINIMAP_HEIGHT)
               {
                   my_mlx_pixel_put(&game->minimap, pixelX, pixelY, 0X00FF0000);
               }
           }
       }
   }
}
void clear_minimap(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (i < MINIMAP_WIDTH)
	{
		j = 0;
		while (j < MINIMAP_HEIGHT)
		{
			my_mlx_pixel_put(&game->minimap, i, j, game->walls.floor);
			j++;
		}
		i++;
	}
}
void drawMap(t_game *game)
{
	clear_minimap(game);
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
	drawMap(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->mlx.data.img, 0, 0);
	mlx_put_image_to_window(game->minimap.img, game->mlx.win, game->minimap.img, 0, 0);
	return 0;
}
