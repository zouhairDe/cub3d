/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:15:34 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/08 11:02:19 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	info_init(t_dda *info)
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

void	get_horizontal_info(t_game *game, t_ray *ray, t_dda *info)
{
	double	xinter;
	double	yinter;
	double	xstep;
	double	ystep;

	yinter = floor(game->player.x) + (double)(ray->facing_down);
	xinter = game->player.y + ((yinter - game->player.x) / tan(ray->angle));
	ystep = 1 + (ray->facing_up * -2);
	xstep = (1 / tan(ray->angle));
	if ((ray->facing_left && xstep > 0) || (ray->facing_right && xstep < 0))
		xstep *= -1;
	info->hdist += distance(game->player.y, game->player.x, xinter, yinter);
	while (1)
	{
		if (is_wall(game, xinter, yinter - (ray->facing_up * 0.00000001)))
			break ;
		info->hdist += distance(xinter, yinter, xinter + xstep, yinter + ystep);
		xinter += xstep;
		yinter += ystep;
	}
	info->hp.x = xinter;
	info->hp.y = yinter;
}

void	get_vertical_info(t_game *game, t_ray *ray, t_dda *info)
{
	double	xinter;
	double	yinter;
	double	xstep;
	double	ystep;

	xinter = floor(game->player.y) + (double)(ray->facing_right);
	yinter = game->player.x + ((xinter - game->player.y) * tan(ray->angle));
	xstep = 1 + (ray->facing_left * -2);
	ystep = tan(ray->angle);
	if ((ray->facing_up && ystep > 0) || (ray->facing_down && ystep < 0))
		ystep *= -1;
	info->vdist += distance(game->player.y, game->player.x, xinter, yinter);
	while (1)
	{
		if (is_wall(game, xinter - (ray->facing_left * 0.00000001), yinter))
			break ;
		info->vdist += distance(xinter, yinter, xinter + xstep, yinter + ystep);
		xinter += xstep;
		yinter += ystep;
	}
	info->vp.x = xinter;
	info->vp.y = yinter;
}

void	set_ray_data(t_dda *info, t_ray *ray, double px, double py)
{
	if (info->vdist < info->hdist)
	{
		ray->dist = info->vdist;
		ray->wall_hit.x = info->vp.x;
		ray->wall_hit.y = info->vp.y;
		ray->vertical_hit = true;
		if (px < ray->wall_hit.x)
			ray->face = W;
		else
			ray->face = E;
	}
	else
	{
		ray->dist = info->hdist;
		ray->wall_hit.x = info->hp.x;
		ray->wall_hit.y = info->hp.y;
		ray->vertical_hit = false;
		if (py < ray->wall_hit.y)
			ray->face = N;
		else
			ray->face = S;
	}
}

void	dda(t_game *game, t_ray *ray)
{
	t_dda	info;

	info_init(&info);
	get_horizontal_info(game, ray, &info);
	get_vertical_info(game, ray, &info);
	set_ray_data(&info, ray, game->player.y, game->player.x);
}
