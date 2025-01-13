/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:19:11 by mait-lah          #+#    #+#             */
/*   Updated: 2025/01/13 01:22:43 by mait-lah         ###   ########.fr       */
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

void putCircle(t_game *game,int X,int Y, int px, int py, int color)
{
    int radius = 3;
	
	int centerX = MINIMAP_WIDTH / 2;
    int centerY = MINIMAP_HEIGHT / 2;

	
	printf("trying to circle  at %d , %d \n" , centerX + X, centerY +Y);
    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            if (x*x + y*y <= radius*radius)
            {
                int pixelX = X + x;
                int pixelY = Y + y;
				
                if (pixelX >= 0 && pixelX < WINDOW_WIDTH && 
                    pixelY >= 0 && pixelY < WINDOW_HEIGHT)
                {
                    my_mlx_pixel_put(&game->mlx.data, centerX +  pixelX- px, centerY + pixelY- py, color);
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
int	is_wall(t_game *game, double playerX, double playerY)
{
	printf("X %f y %f \n", floor(playerX), floor(playerY));
	if (playerX<0 || playerX>game->map.maxCols || playerY<0 || playerY>=game->map.rows)
	{
		printf("out of bounds wall check.");
		return true;
	}
	return ((game->map.map[(int)(playerY-0.000000000001)][(int)(playerX-0.000000000001)] == '1') || (game->map.map[(int)(playerY+0.000000000001)][(int)(playerX+0.000000000001)] == '1'));
}
info_init(t_dda *info)
{
	info->hp.x = 0;
	info->hp.y = 0;
    info->vp.x = 0;
	info->vp.y = 0;
    info->hdist = 0;
    info->vdist = 0;
    info->initial_x = 0;
    info->initial_y = 0;
}

void	dda(t_game *game, t_ray *ray)
{
	t_dda info;
	info_init(&info);
	
	double xintercept = 0;
	double yintercept = 0;
	double xstep = 0;
	double ystep = 0;
	double angle_tan = tan(ray->angle);
	
	t_point Player = {game->player.y, game->player.x};
	
	// finding the first horizontal intersection s cords
	yintercept = floor(Player.y) + (double)(ray->is_facing_down);
	xintercept = Player.x + ((yintercept - Player.y) /  angle_tan);

	printf("player x %f xintercept %f\n",Player.x, xintercept);
	printf("player y %f yintercept %f\n", Player.y, yintercept);

	//  find the xstep and ystep
	ystep = 1 + (ray->is_facing_up * -2);
	xstep = (ystep / angle_tan);
	if ((ray->is_facing_left && xstep > 0) || (ray->is_facing_right && xstep < 0))
		xstep *= -1;
	info.hdist += distance(Player.x, Player.y , xintercept ,yintercept);
	double	next_horz_touchx = xintercept;
	double	next_horz_touchy = yintercept;
	printf("angle %.4f xstep %f ystep %f\n", ray->angle, xstep, ystep);
	while (1)
	{
		printf("nhx %f nhy %f\n", next_horz_touchx, next_horz_touchy);
		putCircle(game, next_horz_touchx*MINIMAP_SCALE, next_horz_touchy*MINIMAP_SCALE, Player.x*MINIMAP_SCALE, Player.y*MINIMAP_SCALE, 0XFF0000);
		if(is_wall(game, next_horz_touchx, next_horz_touchy))
			break;
		info.hdist += distance(next_horz_touchx, next_horz_touchy, next_horz_touchx+xstep, next_horz_touchy+ystep);
		next_horz_touchx += xstep;
		next_horz_touchy += ystep;
	}
	
	//vars reset
	xintercept = floor(Player.x);
	yintercept =  Player.y + ((xintercept - Player.x) *  angle_tan);
	
	xstep = 1 + (ray->is_facing_left * -2);
	ystep = (xstep * angle_tan);

	info.vdist += distance(Player.x, Player.y , xintercept ,yintercept);
	double	next_vert_touchx = xintercept;
	double	next_vert_touchy = yintercept;
	printf("angle %.4f xstep %f ystep %f\n", ray->angle, xstep, ystep);
	while (1)
	{
		printf("nhx %f nhy %f\n", next_vert_touchx, next_vert_touchy);
		putCircle(game, next_vert_touchx*MINIMAP_SCALE, next_vert_touchy*MINIMAP_SCALE, Player.x*MINIMAP_SCALE, Player.y*MINIMAP_SCALE, 0XFFFF00);
		if(is_wall(game, next_vert_touchx, next_vert_touchy))
			break;
		info.vdist += distance(next_vert_touchx, next_vert_touchy, next_vert_touchx+xstep, next_vert_touchy+ystep);
		next_vert_touchx += xstep;
		next_vert_touchy += ystep;
	}
	
	// draw vertical points
	
	info.hp.x = next_horz_touchx;
	info.hp.y = next_horz_touchy;
	printf("\nhorz dist to wall %f\n", info.hdist);
	printf("\vert dist to wall %f\n", info.vdist);
}

t_point	*castRay(t_game *game, t_ray *ray) // for each point on the ray check if its inside a block if so return its x and y since it will the the contact point
{
	t_point *contact_point = malloc(sizeof(t_point));
	//dda algo
    dda(game, ray);
    return (contact_point);
}

void	draw_strip(t_game *game,int x, double length, int color)
{
	double v = length / 2;
	for(int i = 0; i < v;i++)
	{
		my_mlx_pixel_put(&game->mlx.data, x, (WINDOW_HEIGHT / 2 ) + i, color);
		if ((WINDOW_HEIGHT / 2 ) - i < MINIMAP_HEIGHT && x < MINIMAP_WIDTH)
			continue;
		my_mlx_pixel_put(&game->mlx.data, x, (WINDOW_HEIGHT / 2 ) - i, color);
	}
}

void	init_ray(t_ray *ray, double angle)
{
	ray->angle = angle;
	ray->is_facing_down = angle < M_PI && angle > 0;
	ray->is_facing_up = !ray->is_facing_down;
	ray->is_facing_right = angle < (M_PI / 2) || angle > (M_PI * 1.5);
	ray->is_facing_left = !ray->is_facing_right;
	
}

void	castRays(t_game *game)
{
	t_point *contact;
	t_ray *ray;
	int lineLength = 100;
	double angle = game->player.dir ;//- DEG_TO_RAD(FOV / 2);
	
	double ratio = (double)(FOV) / NUM_RAYS;
	//for(int i  = 0; i < 1;i++)
	//{
		double dist;
		ray = malloc(sizeof(t_ray));
		printf("initial angle %f\n", angle);
		init_ray(ray, angle);
		contact = castRay(game, ray);
		//dist = distance(centerX, contact->y, contact->x, contact->y);
		//printf("x y px yx ray size %f\n", dist);
		//draw_strip(game, i, (int)(WINDOW_HEIGHT - (int)(dist * (WINDOW_HEIGHT / MINIMAP_HEIGHT))) , 0x808080);
		angle += DEG_TO_RAD(ratio);
		//free(contact);
		//printf("angle:%f\n",angle);
	//}
}

