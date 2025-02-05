/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:15:34 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/05 12:15:46 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"


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
	double xintercept = 0;
	double yintercept = 0;
	double xstep = 0;
	double ystep = 0;
	double angle_tan = tan(ray->angle);

	t_point player = {game->player.y, game->player.x};

	yintercept = floor(player.y) + (double)(ray->is_facing_down);
	xintercept = player.x + ((yintercept - player.y) /  angle_tan);

	ystep = 1 + (ray->is_facing_up * -2);

	xstep = (1 / angle_tan);

	if ((ray->is_facing_left && xstep > 0) || (ray->is_facing_right && xstep < 0))
		xstep *= -1;

	info->hdist += distance(player.x, player.y , xintercept ,yintercept);

	double	next_horz_touchx = xintercept;
	double	next_horz_touchy = yintercept;

	while (1)
	{

		if(is_wall(game, next_horz_touchx, next_horz_touchy - (ray->is_facing_up * 0.00000001)))
			break;
		info->hdist += distance(next_horz_touchx, next_horz_touchy, next_horz_touchx+xstep, next_horz_touchy+ystep);
		next_horz_touchx += xstep;
		next_horz_touchy += ystep;
	}

	info->hp.x = next_horz_touchx;
	info->hp.y = next_horz_touchy;
}
void	get_vertical_info(t_game *game, t_ray *ray, t_dda *info)
{
	double xintercept = 0;
	double yintercept = 0;
	double xstep = 0;
	double ystep = 0;
	double angle_tan = tan(ray->angle);
	t_point player = {game->player.y, game->player.x};

	xintercept = floor(player.x) + (double)(ray->is_facing_right);
	yintercept =  player.y + ((xintercept - player.x) *  angle_tan);

	xstep = 1 + (ray->is_facing_left * -2);
	ystep = angle_tan;

	if ((ray->is_facing_up && ystep > 0) || (ray->is_facing_down && ystep < 0))
		ystep *= -1;

	info->vdist += distance(player.x, player.y , xintercept ,yintercept);
	double	next_vert_touchx = xintercept;
	double	next_vert_touchy = yintercept;

	while (1)
	{

		if(is_wall(game, next_vert_touchx - (ray->is_facing_left * 0.00000001), next_vert_touchy))
			break;
		info->vdist += distance(next_vert_touchx, next_vert_touchy, next_vert_touchx+xstep, next_vert_touchy+ystep);
		next_vert_touchx += xstep;
		next_vert_touchy += ystep;
	}

	info->vp.x = next_vert_touchx;
	info->vp.y = next_vert_touchy;
}

void	dda(t_game *game, t_ray *ray)
{
	t_dda info;
	info_init(&info);
	t_point player = {game->player.y, game->player.x};

	if (is_wall(game,player.x, player.y))
	{
		ray->dist = 0;
		ray->wallHit.x = player.x;
		ray->wallHit.y = player.y;
		return;
	}

	get_horizontal_info(game , ray, &info);
	get_vertical_info(game , ray, &info);
	if (info.vdist < info.hdist)
	{
		ray->dist = info.vdist;
		ray->wallHit.x = info.vp.x;
		ray->wallHit.y = info.vp.y;
		ray->vertical_hit = true;
		if (player.x < ray->wallHit.x)
			ray->face = W;
		else
			ray->face = E;
	}
	else
	{
		ray->dist = info.hdist;
		ray->wallHit.x = info.hp.x;
		ray->wallHit.y = info.hp.y;
		ray->vertical_hit = false;
		if (player.y < ray->wallHit.y)
			ray->face = N;
		else
			ray->face = S;
	}
}