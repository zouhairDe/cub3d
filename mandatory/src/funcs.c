/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:19:11 by mait-lah          #+#    #+#             */
/*   Updated: 2024/11/26 15:10:47 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void drawLine(t_game *game, int x1, int y1, int x2, int y2, int color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        my_mlx_pixel_put(&game->mlx.data, x1, y1, color);
        if (x1 == x2 && y1 == y2)
            break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void putCircle(t_game *game,int X,int Y)
{
    int radius = 4;

    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            if (x*x + y*y <= radius*radius)
            {
                int pixelX = X + x;
                int pixelY = Y + y;
                
                if (pixelX >= 0 && pixelX < MINIMAP_WIDTH && 
                    pixelY >= 0 && pixelY < MINIMAP_HEIGHT)
                {
                    my_mlx_pixel_put(&game->mlx.data, pixelX, pixelY, 0X000000FF);
                }
            }
        }
    }
}

void drawAngleInMap(t_game *game)
{
	int centerX = MINIMAP_WIDTH / 2;
    int centerY = MINIMAP_HEIGHT / 2;

    int lineLength = 40;


    int endX = centerX + lineLength * cos(game->player.dir);
    int endY = centerY + lineLength * sin(game->player.dir);

    drawLine(game, centerX, centerY, endX, endY, 0X0000FF);
	
}

void drawFovInMap(t_game *game)
{
	int centerX = MINIMAP_WIDTH / 2;
    int centerY = MINIMAP_HEIGHT / 2;

    int lineLength = 60;


    int endX = centerX + lineLength * (cos(game->player.dir - DEG_TO_RAD(FOV / 2)));
    int endY = centerY + lineLength * (sin(game->player.dir - DEG_TO_RAD(FOV / 2)));

    drawLine(game, centerX, centerY, endX, endY, 0X00FF00);
	
	endX = centerX + lineLength * (cos(game->player.dir + DEG_TO_RAD(FOV / 2)) );
    endY = centerY + lineLength * (sin(game->player.dir + DEG_TO_RAD(FOV / 2) ) );

    drawLine(game, centerX, centerY, endX, endY, 0X00FF00);
	
}
int DEBUG =  true;


t_point	*castRay(t_game *game, double angle) // for each point on the ray check if its inside a block if so return its x and y since it will the the contact point
{
	t_point *contact_point = malloc(sizeof(t_point));
	int centerX = MINIMAP_WIDTH / 2;
    int centerY = MINIMAP_HEIGHT / 2;
	double p = 1;
	// do logic
	while(1)//p < 50)
	{
		int pointX = centerX + p * cos(angle);
    	int pointY = centerY + p * sin(angle);
		int playerX = (game->player.x * SCALE) +  p * (sin(angle) / 2 );
    	int playerY = (game->player.y * SCALE) +  p * (cos(angle) / 2 );
		//printf("cx: %d cy: %d x: %d y: %d square?: '%c'\n", centerX, centerY, pointX1 , pointY1, game->map.map[squareY][squareX]);
		if (game->map.map[(int)(playerX / SCALE)][(int)(playerY / SCALE)] == '1')
		{
			contact_point->x = pointX;
			contact_point->y = pointY;
			break;
		}
		//drawLine(game, centerX, centerY, pointX, pointY, 0XFF0000);
		my_mlx_pixel_put(&game->mlx.data, pointX, pointY, 0X00FF0000);
		p++;
	}
	return (contact_point);
}

void	draw_strip(t_game *game,int x, double length, int color)
{
	double v = length /2;
	for(int i = 0; i < v;i++)
	{
		my_mlx_pixel_put(&game->mlx.data, x, (WINDOW_HEIGHT / 2 ) - i, color);
		my_mlx_pixel_put(&game->mlx.data, x, (WINDOW_HEIGHT / 2 ) + i, color);
	}
}

void	castRays(t_game *game)
{
	t_point * contact;
	int centerX = MINIMAP_WIDTH / 2;
    int centerY = MINIMAP_HEIGHT / 2;
	int lineLength = 100;
	double angle = game->player.dir - DEG_TO_RAD(FOV / 2);
	double ratio = (double)(FOV) / WINDOW_WIDTH;
	for(int i  = 0; i < WINDOW_WIDTH;i++)
	{
		int pointX = centerX + lineLength * (cos(angle));
    	int pointY = centerY + lineLength * (sin(angle));
		double dist;
		contact = castRay(game, angle);
		dist = distance(centerX, contact->y, contact->x, contact->y);
		printf("x y px yx ray size %f\n", dist);
		draw_strip(game, i, (int)(WINDOW_HEIGHT - (int)(dist * (WINDOW_HEIGHT / MINIMAP_HEIGHT))) , 0x808080);
		angle += DEG_TO_RAD(ratio);
		//printf("angle:%f\n",angle);
	}
}

