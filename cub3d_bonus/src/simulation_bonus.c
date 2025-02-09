/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 06:49:38 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/09 08:54:41 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	draw_tile_pixel(t_game *game, t_minimap *vars, int i, int j)
{
	if (game->map.map[i][j] == '1')
	{
		vars->color = ((unsigned int *)game->walls.wt.addr)[vars->ty
			* (WALL_SIZE / 2) + vars->tx];
		my_mlx_pixel_put(&game->minimap, vars->pixel_x,
			vars->pixel_y, vars->color);
	}
	else if (game->map.map[i][j] == 'D')
		my_mlx_pixel_put(&game->minimap, vars->pixel_x,
			vars->pixel_y, 0x000000);
	else if (game->map.map[i][j] == 'd')
		my_mlx_pixel_put(&game->minimap, vars->pixel_x,
			vars->pixel_y, 0xC8C8C8);
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
	t_point			pl;
	t_minimap		vars;
	int				i;
	int				j;
	int				col;

	i = 0;
	pl.x = game->player.y;
	pl.y = game->player.x;
	vars.rotationAngle = game->player.dir;
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

void	center_player_in_map(t_game *game)
{
	int	radius;
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
				if (pixel_x >= 0 && pixel_x < MINIMAP_WIDTH
					&& pixel_y >= 0 && pixel_y < MINIMAP_HEIGHT)
					my_mlx_pixel_put(&game->minimap, pixel_x,
						pixel_y, 0X00FF0000);
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

void	draw_map(t_game *game)
{
	clear_minimap(game);
	draw_rotated_map(game);
	center_player_in_map(game);
	draw_angle_in_map(game);
	draw_fov_in_map(game);
}

void	clean_window(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		j = 0;
		while (j < WINDOW_HEIGHT)
		{
			my_mlx_pixel_put(data, i, j, 0X00CDD0D4);
			j++;
		}
		i++;
	}
}

void	draw_diagonal_lines(t_game *game, int i)
{
	int			j;
	int			k;
	t_intPoint	point1;
	t_intPoint	point2;

	j = -(game->crosshair.thickness / 2) - 1;
	while (++j <= game->crosshair.thickness / 2)
	{
		k = -(game->crosshair.thickness / 2) - 1;
		while (++k <= game->crosshair.thickness / 2)
		{
			point1.x = WIN_CENTER_X + i + j;
			point1.y = WIN_CENTER_Y + i + k;
			if (point1.x >= 0 && point1.x < WINDOW_WIDTH && point1.y >= 0
				&& point1.y < WINDOW_HEIGHT)
				my_mlx_pixel_put(&game->mlx.data, point1.x, point1.y,
					0X00FFFFFF);
			point2.x = WIN_CENTER_X + i + j;
			point2.y = WIN_CENTER_Y - i + k;
			if (point2.x >= 0 && point2.x < WINDOW_WIDTH && point2.y >= 0
				&& point2.y < WINDOW_HEIGHT)
				my_mlx_pixel_put(&game->mlx.data, point2.x, point2.y,
					0X00FFFFFF);
		}
	}
}

void	draw_crosshair(t_game *game)
{
	int	i;

	i = -game->crosshair.size;
	while (i <= game->crosshair.size)
	{
		draw_diagonal_lines(game, i);
		i++;
	}
}

int	simulate(t_game *game)
{
	mlx_clear_window(game->mlx.mlx, game->mlx.win);
	clean_window(&game->mlx.data);
	collor_ceilling(game);
	collor_floor(game);
	cast_rays(game);
	draw_crosshair(game);
	draw_map(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win,
		game->mlx.data.img, 0, 0);
	mlx_put_image_to_window(game->minimap.img, game->mlx.win,
		game->minimap.img, 0, 0);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win,
		game->sprites_image, 0, 0);
	mlx_do_sync(game->mlx.mlx);
	return (0);
}
