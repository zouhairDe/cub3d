/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:01:28 by zouddach          #+#    #+#             */
/*   Updated: 2024/09/21 21:33:34 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"

void	init_ray(t_ray *ray, t_game *game)
{
	ray->x = game->player.x;
	ray->y = game->player.y;
	ray->dir = game->player.dir - (game->player.fov / 2);
	ray->angle = game->player.dir;
	ray->dist = 0.0;
	ray->wallStripHeight = 0.0;
	ray->hit = 0;
}

void	cast_ray(t_game *game, t_ray *ray)
{
	double xstep;
	double ystep;
	double xintercept;
	double yintercept;
	double xtocheck;
	double ytocheck;

	xstep = cos(ray->dir) > 0 ? 1 : -1;
	ystep = sin(ray->dir) > 0 ? 1 : -1;
	xintercept = floor(game->player.x);
	xintercept += cos(ray->dir) > 0 ? 1 : 0;
	yintercept = game->player.y + (xintercept - game->player.x) * tan(ray->dir);
	xtocheck = xintercept;
	ytocheck = yintercept;
	while (xtocheck >= 0 && xtocheck < game->map.maxCols && ytocheck >= 0 && ytocheck < game->map.rows)
	{
		if (game->map.map[(int)ytocheck][(int)xtocheck] == '1')
		{
			ray->hit = 1;
			ray->wallHitX = xtocheck;
			ray->wallHitY = ytocheck;
			break ;
		}
		else
		{
			xtocheck += xstep;
			ytocheck += ystep;
		}
	}
	ray->dist = (ray->hit) ? sqrt(pow(game->player.x - ray->wallHitX, 2) + pow(game->player.y - ray->wallHitY, 2)) : 0;
}