/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:14:05 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/10 02:50:29 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	handle_press2(int keycode, t_game	*game)
{
	if (keycode == W_BUTTON && check_wall_collision(game, W_BUTTON))
	{
		game->player.x += game->player.moving_speed * sin(game->player.dir);
		game->player.y += game->player.moving_speed * cos(game->player.dir);
	}
	else if (keycode == S_BUTTON && check_wall_collision(game, S_BUTTON))
	{
		game->player.x -= game->player.moving_speed * sin(game->player.dir);
		game->player.y -= game->player.moving_speed * cos(game->player.dir);
	}
	else if (keycode == A_BUTTON && check_wall_collision(game, A_BUTTON))
	{
		game->player.x -= game->player.moving_speed * cos(game->player.dir);
		game->player.y += game->player.moving_speed * sin(game->player.dir);
	}
	else if (keycode == D_BUTTON && check_wall_collision(game, D_BUTTON))
	{
		game->player.x += game->player.moving_speed * cos(game->player.dir);
		game->player.y -= game->player.moving_speed * sin(game->player.dir);
	}
}

int	handle_press(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == 53)
		return (quit(param));
	if (keycode == H_BUTTON && game->mouse)
		(mlx_mouse_hide(), game->mouse = !game->mouse);
	else if (keycode == H_BUTTON && !game->mouse)
		(mlx_mouse_show(), game->mouse = !game->mouse);
	else if (keycode == LEFT_BUTTON)
		game->player.dir -= game->player.rotation_speed;
	else if (keycode == RIGHT_BUTTON)
		game->player.dir += game->player.rotation_speed;
	handle_press2(keycode, game);
	game->player.dir = normalize_angle(game->player.dir);
	return (0);
}

int	handle_release(int keycode, void *param)
{
	t_game	*game;

	keycode = 0;
	game = (t_game *)param;
	return (0);
}

int	handle_mouse(int x, int y, void *param)
{
	t_game		*game;
	int			diff_x;
	static int	last_x;

	y = 0;
	game = (t_game *)param;
	last_x = WINDOW_WIDTH / 2;
	diff_x = x - last_x;
	if (game->mouse)
		return (0);
	if (diff_x != 0)
	{
		game->player.dir += (diff_x * 0.001);
		game->player.dir = normalize_angle(game->player.dir);
		last_x = x;
	}
	mlx_mouse_move(game->mlx.win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	return (0);
}
