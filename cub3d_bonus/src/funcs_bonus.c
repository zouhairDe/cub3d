/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:19:11 by mait-lah          #+#    #+#             */
/*   Updated: 2025/02/10 17:49:50 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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
	if (ray->wall_content == DOOR_CLOSED)
		c = ((unsigned int *)game->walls.closed_door.addr)[ty * WALL_SIZE + tx];
	c += ((int)(ray->dist * 6) << 24);
	return (c);
}

void	init_drawing_data(t_drawing_data *data, t_game *game, t_ray *ray)
{
	data->angle_diff = ray->angle - game->player.dir;
	data->perp_dist = cos(data->angle_diff) * ray->dist;
	data->projection_plan_dist = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	data->strip_height = data->projection_plan_dist / data->perp_dist;
	data->start = (WINDOW_HEIGHT / 2) - (data->strip_height / 2);
	data->end = (WINDOW_HEIGHT / 2) + (data->strip_height / 2);
	data->tx = -1;
	data->y = data->start;
	data->dft = 0;
	data->ty = 0;
}

void	draw_stripe(t_game *game, int x, t_ray *ray)
{
	t_drawing_data	data;

	init_drawing_data(&data, game, ray);
	if (data.start < 0)
		data.start = 0;
	if (data.end > WINDOW_HEIGHT)
		data.end = WINDOW_HEIGHT;
	if (ray->vertical_hit)
		data.tx = (int)(ray->wall_hit.y * WALL_SIZE) % WALL_SIZE;
	else
		data.tx = (int)(ray->wall_hit.x * WALL_SIZE) % WALL_SIZE;
	while (data.y < data.end)
	{
		data.dft = data.y + ((data.strip_height / 2) - (WINDOW_HEIGHT / 2));
		data.ty = data.dft * ((double)WALL_SIZE / data.strip_height);
		my_mlx_pixel_put(&game->mlx.data, x, data.y, get_color(game, ray,
				data.tx, data.ty));
		data.y++;
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
	ray->wall_hit.x = 0;
	ray->wall_hit.y = 0;
	ray->wall_content = DOOR_OPEN;
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
		init_ray(ray, normalize_angle((angle)));
		dda(game, ray);
		draw_stripe(game, i, ray);
		free_ptr(game, ray);
		angle += ratio;
		i++;
	}
}
