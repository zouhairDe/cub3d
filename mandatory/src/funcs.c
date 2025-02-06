/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:19:11 by mait-lah          #+#    #+#             */
/*   Updated: 2025/02/06 16:10:16 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_wall(t_game *game, double pX, double pY)
{
	if (pX<=0 || pX>=game->map.maxCols || pY<=0 || pY>=game->map.rows)
		return true;
	return ((game->map.map[(int)(pY)][(int)(pX)] == '1'));
}

void	draw_stripe(t_game *game,int x, t_ray *ray)
{
	double angle_diff =  normalizeAngle(ray->angle - game->player.dir);
	double perp_dist = cos(angle_diff) * ray->dist;
	double PROJECTION_PLANE_DIST  = ((double)WINDOW_WIDTH / 2) / tan((double)FOV/2);
	int stripHeight = (int)((1 / perp_dist) * PROJECTION_PLANE_DIST);

	int start = (WINDOW_HEIGHT / 2) - (stripHeight / 2);
	int end = (WINDOW_HEIGHT / 2) + (stripHeight / 2);

	if (stripHeight < 0)
	{
		for(int y = 0; y < WINDOW_HEIGHT;y++)
		{
			my_mlx_pixel_put(&game->mlx.data, x, y, 0xFF0000);
		}
		return;
	}
	
	if (start < 0)
		start = 0;
	if (end > WINDOW_HEIGHT)
		end = WINDOW_HEIGHT;
	int tx = -1;
	if (ray->vertical_hit)
		tx = (int)(ray->wallHit.y * WALL_SIZE) % WALL_SIZE;
	else
		tx = (int)(ray->wallHit.x * WALL_SIZE) % WALL_SIZE;

	for(int y = start; y < end;y++)
	{
		int dft = y + (stripHeight /2) - (WINDOW_HEIGHT / 2);
		int ty = dft * ((double)WALL_SIZE / stripHeight);
		unsigned int c = 0;
		if (ray->face == N)
			c = ((unsigned int *)game->walls.no.addr)[ty * WALL_SIZE + tx];
		else if (ray->face == E)
			c = ((unsigned int *)game->walls.ea.addr)[ty * WALL_SIZE + tx];
		else if (ray->face == S)
			c = ((unsigned int *)game->walls.so.addr)[ty * WALL_SIZE + tx];
		else if (ray->face == W)
			c = ((unsigned int *)game->walls.we.addr)[ty * WALL_SIZE + tx];
		c += ((int)(ray->dist * 6) << 24); // alpha
		my_mlx_pixel_put(&game->mlx.data, x, y, c);
	}
}

void	init_ray(t_ray *ray, double angle)
{
	ray->angle = angle;
	ray->facing_down = angle < M_PI && angle > 0;
	ray->facing_up = !ray->facing_down;
	ray->facing_right = angle < (M_PI / 2) || angle > (M_PI * 1.5);
	ray->facing_left = !ray->facing_right;
	ray->vertical_hit = false;
	ray->dist = 0;
	ray->wallHit.x = 0;
	ray->wallHit.y = 0;
}

//void logs(double angle, double ray_dist, double stripHeight, t_game *game, t_ray *ray)
//{
//    struct stat st = {0};
//    if (stat("logs", &st) == -1) {
//        mkdir("logs", 0700);
//    }

//    FILE *f = fopen("logs/logs.log", "a");
//    if (!f) {
//        perror("Error opening log file");
//        return;
//    }

//    fprintf(f, " ------------------- initial angle %f --- - - - - - - - - -\n", angle);
//    fprintf(f, "player at %f %f hit wall at %f %f with dist %f\n", game->player.y, game->player.x, ray->wallHit.x, ray->wallHit.y, ray->dist);
//    //fprintf(f, "proj plane  dist %f\n", PROJECTION_PLANE_DIST);
//    fprintf(f, "ray dist %f\n", ray_dist);
//    fprintf(f, "strip height %f\n", stripHeight);

//    fclose(f);
//}

void	castRays(t_game *game)
{
	t_ray *ray;
	t_point player = {game->player.y, game->player.x};
	double angle;
	double ratio;

	angle = game->player.dir - (FOV / 2);
	ratio = FOV / NUM_RAYS;
	for(int i  = 0; i < NUM_RAYS;i++)
	{
		double dist;
		ray = g_malloc(game, sizeof(t_ray));
		init_ray(ray, normalizeAngle((angle)));
		dda(game, ray);
		draw_stripe(game, i, ray);
		angle += ratio;
		free_ptr(game, ray);
	}
}

