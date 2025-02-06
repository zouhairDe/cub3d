/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_funcs_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:15:34 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/06 18:51:02 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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
	info->vwall = false;
	info->hwall = false;
}

void	get_horizontal_info(t_game *game, t_ray *ray, t_dda *info)
{
	double	xi;
	double	yi;
	double	xstep;
	double	ystep;

	yi = floor(game->player.x) + (double)(ray->facing_down);
	xi = game->player.y + ((yi - game->player.x) / tan(ray->angle));
	ystep = 1 + (ray->facing_up * -2);
	xstep = (1 / tan(ray->angle));
	if ((ray->facing_left && xstep > 0) || (ray->facing_right && xstep < 0))
		xstep *= -1;
	info->hdist += distance(game->player.y, game->player.x, xi, yi);
	while (1)
	{
		if (is_wall(game, xi, yi - (ray->facing_up * 0.00000001)))
			break ;
		info->hwall = door(game, xi, yi - (ray->facing_up * 0.00000001), ray);
		if (info->hwall)
			break ;
		info->hdist += distance(xi, yi, xi + xstep, yi + ystep);
		xi += xstep;
		yi += ystep;
	}
	info->hp.x = xi;
	info->hp.y = yi;
}

void	get_vertical_info(t_game *game, t_ray *ray, t_dda *info)
{
	double	xi;
	double	yi;
	double	xstep;
	double	ystep;

	xi = floor(game->player.y) + (double)(ray->facing_right);
	yi = game->player.x + ((xi - game->player.y) * tan(ray->angle));
	xstep = 1 + (ray->facing_left * -2);
	ystep = tan(ray->angle);
	if ((ray->facing_up && ystep > 0) || (ray->facing_down && ystep < 0))
		ystep *= -1;
	info->vdist += distance(game->player.y, game->player.x, xi, yi);
	while (1)
	{
		if (is_wall(game, xi - (ray->facing_left * 0.00000001), yi))
			break ;
		info->vwall = door(game, xi - (ray->facing_left * 0.00000001), yi, ray);
		if (info->vwall)
			break ;
		info->vdist += distance(xi, yi, xi + xstep, yi + ystep);
		xi += xstep;
		yi += ystep;
	}
	info->vp.x = xi;
	info->vp.y = yi;
}

void	set_ray_data(t_dda *info, t_ray *ray, double px, double py)
{
	if (info->vdist < info->hdist)
	{
		ray->dist = info->vdist;
		ray->wallHit.x = info->vp.x;
		ray->wallHit.y = info->vp.y;
		ray->vertical_hit = true;
		if (px < ray->wallHit.x)
			ray->face = W;
		else
			ray->face = E;
		ray->wallContent = DOOR_CLOSED + (!info->vwall);
	}
	else
	{
		ray->dist = info->hdist;
		ray->wallHit.x = info->hp.x;
		ray->wallHit.y = info->hp.y;
		ray->vertical_hit = false;
		if (py < ray->wallHit.y)
			ray->face = N;
		else
			ray->face = S;
		ray->wallContent = DOOR_CLOSED + (!info->hwall);
	}
}

void	dda(t_game *game, t_ray *ray)
{
	t_dda	info;

	info_init(&info);
	if (is_wall(game, game->player.y, game->player.x))
	{
		ray->dist = 0;
		ray->wallHit.x = game->player.y;
		ray->wallHit.y = game->player.x;
		return ;
	}
	get_horizontal_info(game, ray, &info);
	get_vertical_info(game, ray, &info);
	set_ray_data(&info, ray, game->player.y, game->player.x);
}
