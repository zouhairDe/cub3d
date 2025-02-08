/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 06:49:38 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/08 17:23:40 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

double normalize_angle(double angle)
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

			my_mlx_pixel_put(&game->mlx.data, i, j, game->walls.ceilling);
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
			my_mlx_pixel_put(&game->mlx.data, i, j, game->walls.floor);
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
           int screenX = CENTER_X + (int)mapX;
           int screenY = CENTER_Y + (int)mapY;

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
			else if (game->map.map[i][j] == 'D')
			{
				for (int y = 0; y < MINIMAP_SCALE; y++)
				{
					for (int x = 0; x < MINIMAP_SCALE; x++)
					{
						int pixelX = screenX + x;
						int pixelY = screenY + y;
						if (pixelX >= 0 && pixelX < MINIMAP_WIDTH && pixelY >= 0 && pixelY < MINIMAP_HEIGHT)
						{
							int tx = (pixelX-screenX) % (WALL_SIZE/2);
							int ty = (pixelY-screenY) % (WALL_SIZE/2);
							my_mlx_pixel_put(&game->minimap, pixelX, pixelY, 0x000000);
						}
					}
				}
			}
			else if (game->map.map[i][j] == 'd')
			{
				for (int y = 0; y < MINIMAP_SCALE; y++)
				{
					for (int x = 0; x < MINIMAP_SCALE; x++)
					{
						if (x % MINIMAP_SCALE > 2 && x % MINIMAP_SCALE < MINIMAP_SCALE-2 && y % MINIMAP_SCALE > 2 && y % MINIMAP_SCALE < MINIMAP_SCALE-2)
							continue;

						int pixelX = screenX + x;
						int pixelY = screenY + y;
						if (pixelX >= 0 && pixelX < MINIMAP_WIDTH && pixelY >= 0 && pixelY < MINIMAP_HEIGHT)
						{
							int tx = (pixelX-screenX) % (WALL_SIZE/2);
							int ty = (pixelY-screenY) % (WALL_SIZE/2);

							my_mlx_pixel_put(&game->minimap, pixelX, pixelY, 0x000000);
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
               int pixelX = CENTER_X + x;
               int pixelY = CENTER_Y + y;

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
	drawAngleInMap(game); 
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
			point1.x = WIN_CENTER_X + i + j;
			point1.y = WIN_CENTER_Y + i + k;
			if (point1.x >= 0 && point1.x < WINDOW_WIDTH && point1.y >= 0 && point1.y < WINDOW_HEIGHT)
				my_mlx_pixel_put(&game->mlx.data, point1.x, point1.y, 0X00FFFFFF);
			point2.x = WIN_CENTER_X + i + j;
			point2.y = WIN_CENTER_Y - i + k;
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

	mlx_clear_window(game->mlx.mlx, game->mlx.win);
	clean_window(&game->mlx.data);
	collorCeilling(game);
	collorFloor(game);
	cast_rays(game);
	draw_crosshair(game);
	drawMap(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->mlx.data.img, 0, 0);
	mlx_put_image_to_window(game->minimap.img, game->mlx.win, game->minimap.img, 0, 0);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->sprites_image, 0, 0);

	mlx_do_sync(game->mlx.mlx);
	return 0;
}
