/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:19:11 by mait-lah          #+#    #+#             */
/*   Updated: 2025/02/08 07:00:06 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_wall(t_game *game, double pX, double pY)
{
	if (pX <= 0 || pX >= game->map.maxCols || pY <= 0 || pY >= game->map.rows)
		return (true);
	return ((game->map.map[(int)(pY)][(int)(pX)] == '1'));
}

unsigned int	get_color(t_game *game, t_ray *ray, int tx, int ty)
{
	int	c;

	c = 0;
	if (ray->face == N)
		c = ((unsigned int *)game->walls.no.addr)[ty * WALL_SIZE + tx];
	else if (ray->face == E)
		c = ((unsigned int *)game->walls.ea.addr)[ty * WALL_SIZE + tx];
	else if (ray->face == S)
		c = ((unsigned int *)game->walls.so.addr)[ty * WALL_SIZE + tx];
	else if (ray->face == W)
		c = ((unsigned int *)game->walls.we.addr)[ty * WALL_SIZE + tx];
	c += ((int)(ray->dist * 6) << 24);
	return (c);
}

void	draw_stripe(t_game *game, int x, t_ray *ray)
{
	double	angle_diff =  ray->angle - game->player.dir;
	double	perp_dist = cos(angle_diff) * ray->dist;
	double	PROJECTION_PLANE_DIST  = (WINDOW_WIDTH / 2) / tan(FOV/2);
	int		stripHeight = PROJECTION_PLANE_DIST / perp_dist;
	int		start = (WINDOW_HEIGHT / 2) - (stripHeight / 2);
	int		end = (WINDOW_HEIGHT / 2) + (stripHeight / 2);
	int		tx = -1;
	int		y = start;
	
	if (start < 0)
		start = 0;
	if (end > WINDOW_HEIGHT)
		end = WINDOW_HEIGHT;
	if (ray->vertical_hit)
		tx = (int)(ray->wallHit.y * WALL_SIZE) % WALL_SIZE;
	else
		tx = (int)(ray->wallHit.x * WALL_SIZE) % WALL_SIZE;
	while (y < end)
	{
		int dft = y + ((stripHeight /2 ) - (WINDOW_HEIGHT / 2));
		int ty = dft * ((double)WALL_SIZE / stripHeight);
		my_mlx_pixel_put(&game->mlx.data, x, y, get_color(game, ray, tx, ty));
		y++;
	}
}

void	init_ray(t_ray *ray, double angle)
{
	ray->angle = angle;
	ray->facing_down = angle < M_PI && angle > 0;
	ray->facing_up = !ray->facing_down;
	ray->facing_right = angle < (M_PI / 2.0) || angle > (M_PI * 1.5);
	ray->facing_left = !ray->facing_right;
	ray->vertical_hit = false;
	ray->dist = 0;
	ray->wallHit.x = 0;
	ray->wallHit.y = 0;
}

void	cast_rays(t_game *game)
{
	t_ray	*ray;
	int		i;
	double	angle;
	double	ratio;

	i = 0;
	angle = game->player.dir - (FOV / 2.0);
	ratio = FOV / NUM_RAYS;
	while (i < NUM_RAYS)
	{
		ray = g_malloc(game, sizeof(t_ray));
		init_ray(ray, normalizeAngle((angle)));
		dda(game, ray);
		draw_stripe(game, i, ray);
		free_ptr(game, ray);
		angle += ratio;
		i++;
	}
}
