/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:01:28 by zouddach          #+#    #+#             */
/*   Updated: 2024/11/18 13:43:40 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"

// void	draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY, int color)
// {
// 	double deltaX = endX - beginX; // 10
// 	double deltaY = endY - beginY; // 0

// 	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
// 	//  pixels = sqrt((10 * 10) + (0 * 0)) = sqrt(100) = 1
	
// 	deltaX /= pixels; // 1
// 	deltaY /= pixels; // 0
// 	double pixelX = beginX;
// 	double pixelY = beginY;
// 	while (pixels)
// 	{
// 	    mlx_pixel_put(mlx, win, pixelX, pixelY, color);
// 	    pixelX += deltaX;
// 	    pixelY += deltaY;
// 	    --pixels;
// 	}
// }

void verLine(void *mlx_ptr, void *win_ptr, int x, int drawStart, int drawEnd, int color) {
    int y;

    // Draw the vertical line from drawStart to drawEnd at position x
    for (y = drawStart; y <= drawEnd; y++) {
        my_mlx_pixel_put(mlx_ptr, x, y, 0xffffff);
    }
}


void	init_ray(t_ray *ray, t_game *game)
{
	ray->origin.x = game->player.x;
	ray->origin.y = game->player.y;
	ray->Dir.x = cos(game->player.dir);
	ray->Dir.y = sin(game->player.dir);
	ray->angle = game->player.dir;
	ray->dist = 0.0;
	ray->wallStripHeight = 0.0;
	ray->hit = 0;
}

void cast_minimap_rays(t_game *game)
{
    double posX = game->player.x;
    double posY = game->player.y;
	double dirX = -1;
	double dirY = 0;
	double planeX = 0 ;
	double planeY = 0.66;

	for (int x = 0; x < WINDOW_WIDTH; x++)
	{
		double cameraX = 2 * x / (double)WINDOW_WIDTH - 1;
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;

		int mapX = (int)posX;
		int mapY = (int)posY;

		double sideDistX;
		double sideDistY;

		double deltaDistX = (rayDirX == 0) ? INT_MAX : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? INT_MAX : fabs(1 / rayDirY);
		double perpWallDist;

		int stepX, stepY;
		int hit = 0;
		int side;

		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		
		 //perform DDA
		while (hit == 0)
		{
		  //jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
		  //Check if ray has hit a wall
		  // if (worldMap[mapX][mapY] > 0) hit = 1;
		  if (game->map.map[mapY][mapX] != '0') hit = 1;

			//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
			if	(side == 0) perpWallDist = (sideDistX - deltaDistX);
			else          perpWallDist = (sideDistY - deltaDistY);

			int h = WINDOW_WIDTH;
			  //Calculate height of line to draw on screen
			int lineHeight = (int)(h / perpWallDist);
			
			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + h / 2;
			if(drawStart < 0)drawStart = 0;
			int drawEnd = lineHeight / 2 + h / 2;
			if(drawEnd >= h)drawEnd = h - 1;

			verLine(game->mlx.mlx, game->mlx.win, x, drawStart, drawEnd, 0);
		} 
	}
}