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
	ray->origin.x = game->player.x;
	ray->origin.y = game->player.y;
	ray->Dir.x = cos(game->player.dir);
	ray->Dir.y = sin(game->player.dir);
	ray->angle = game->player.dir;
	ray->dist = 0.0;
	ray->wallStripHeight = 0.0;
	ray->hit = 0;
}
