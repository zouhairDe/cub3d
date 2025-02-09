/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:24:25 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/09 22:54:40 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	center_player_in_map(t_game *game)
{
	int	pixel_x;
	int	pixel_y;
	int	y;
	int	x;

	y = -4;
	while (y <= 4)
	{
		x = -4;
		while (x <= 4)
		{
			if (x * x + y * y <= 4 * 4)
			{
				pixel_x = CENTER_X + x;
				pixel_y = CENTER_Y + y;
				if (pixel_x >= 0 && pixel_x < MINIMAP_WIDTH && pixel_y >= 0
					&& pixel_y < MINIMAP_HEIGHT)
					my_mlx_pixel_put(&game->minimap, pixel_x, pixel_y,
						0X00FF0000);
			}
			x++;
		}
		y++;
	}
}

void	clear_minimap(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_WIDTH)
	{
		j = 0;
		while (j < MINIMAP_HEIGHT)
		{
			my_mlx_pixel_put(&game->minimap, i, j, game->walls.floor);
			j++;
		}
		i++;
	}
}

void	draw_tile_pixel(t_game *game, t_minimap *vars, int i, int j)
{
	if (game->map.map[i][j] == '1')
	{
		vars->color = ((unsigned int *)game->walls.wt.addr)[vars->ty
			* (WALL_SIZE / 2) + vars->tx];
		my_mlx_pixel_put(&game->minimap, vars->pixel_x, vars->pixel_y,
			vars->color);
	}
	else if (game->map.map[i][j] == 'D')
		my_mlx_pixel_put(&game->minimap, vars->pixel_x, vars->pixel_y,
			0x000000);
	else if (game->map.map[i][j] == 'd')
		my_mlx_pixel_put(&game->minimap, vars->pixel_x, vars->pixel_y,
			0xC8C8C8);
}

void	draw_tile(t_game *game, t_minimap *vars, int i, int j)
{
	int	x;
	int	y;

	x = 0;
	while (x < MINIMAP_SCALE)
	{
		y = 0;
		while (y < MINIMAP_SCALE)
		{
			vars->pixel_x = vars->screen_x + x;
			vars->pixel_y = vars->screen_y + y;
			if (vars->pixel_x >= 0 && vars->pixel_x < MINIMAP_WIDTH
				&& vars->pixel_y >= 0 && vars->pixel_y < MINIMAP_HEIGHT)
			{
				vars->tx = x % (WALL_SIZE / 2);
				vars->ty = y % (WALL_SIZE / 2);
				draw_tile_pixel(game, vars, i, j);
			}
			y++;
		}
		x++;
	}
}

void	draw_rotated_map(t_game *game)
{
	t_point		pl;
	t_minimap	vars;
	int			i;
	int			j;
	int			col;

	i = 0;
	pl.x = game->player.y;
	pl.y = game->player.x;
	vars.rotation_angle = game->player.dir;
	while (i < game->map.rows)
	{
		col = ft_strlen(game->map.map[i]);
		j = 0;
		while (j < col)
		{
			vars.screen_x = CENTER_X + (int)((j - pl.x) * MINIMAP_SCALE);
			vars.screen_y = CENTER_Y + (int)((i - pl.y) * MINIMAP_SCALE);
			draw_tile(game, &vars, i, j);
			j++;
		}
		i++;
	}
}
