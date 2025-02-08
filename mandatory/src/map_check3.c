/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:10:06 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/08 13:00:11 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	check_up_collision(t_game *game, int *newX, int *newY)
{
	*newX = game->player.x + game->player.moving_speed * sin(game->player.dir);
	*newY = game->player.y + game->player.moving_speed * cos(game->player.dir);
	if (game->map.map[(int)*newX][(int)*newY] == '1'
		|| game->map.map[(int)*newX][(int)*newY] == 'D')
		return (false);
	*newX = game->player.x + game->player.moving_speed * sin(game->player.dir
			- 45);
	*newY = game->player.y + game->player.moving_speed * cos(game->player.dir
			- 45);
	if (game->map.map[(int)*newX][(int)*newY] == '1'
		|| game->map.map[(int)*newX][(int)*newY] == 'D')
	{
		*newX = game->player.x + game->player.moving_speed
			* sin(game->player.dir + 45);
		*newY = game->player.y + game->player.moving_speed
			* cos(game->player.dir + 45);
		if (game->map.map[(int)*newX][(int)*newY] == '1'
			|| game->map.map[(int)*newX][(int)*newY] == 'D')
			return (false);
	}
	return (true);
}

bool	check_left_collision(t_game *game, int *newX, int *newY)
{
	*newX = game->player.x - game->player.moving_speed * cos(game->player.dir);
	*newY = game->player.y + game->player.moving_speed * sin(game->player.dir);
	if (game->map.map[(int)*newX][(int)*newY] == '1'
		|| game->map.map[(int)*newX][(int)*newY] == 'D')
		return (false);
	*newX = game->player.x - game->player.moving_speed * cos(game->player.dir
			- 45);
	*newY = game->player.y + game->player.moving_speed * sin(game->player.dir
			- 45);
	if (game->map.map[(int)*newX][(int)*newY] == '1'
		|| game->map.map[(int)*newX][(int)*newY] == 'D')
	{
		*newX = game->player.x - game->player.moving_speed
			* cos(game->player.dir + 45);
		*newY = game->player.y + game->player.moving_speed
			* sin(game->player.dir + 45);
		if (game->map.map[(int)*newX][(int)*newY] == '1'
			|| game->map.map[(int)*newX][(int)*newY] == 'D')
			return (false);
	}
	return (true);
}

bool	check_down_collision(t_game *game, int *newX, int *newY)
{
	*newX = game->player.x - game->player.moving_speed * sin(game->player.dir);
	*newY = game->player.y - game->player.moving_speed * cos(game->player.dir);
	if (game->map.map[(int)*newX][(int)*newY] == '1'
		|| game->map.map[(int)*newX][(int)*newY] == 'D')
		return (false);
	*newX = game->player.x - game->player.moving_speed * sin(game->player.dir
			- 45);
	*newY = game->player.y - game->player.moving_speed * cos(game->player.dir
			- 45);
	if (game->map.map[(int)*newX][(int)*newY] == '1'
		|| game->map.map[(int)*newX][(int)*newY] == 'D')
	{
		*newX = game->player.x - game->player.moving_speed
			* sin(game->player.dir + 45);
		*newY = game->player.y - game->player.moving_speed
			* cos(game->player.dir + 45);
		if (game->map.map[(int)*newX][(int)*newY] == '1'
			|| game->map.map[(int)*newX][(int)*newY] == 'D')
			return (false);
	}
	return (true);
}

bool	check_right_collision(t_game *game, int *newX, int *newY)
{
	*newX = game->player.x + game->player.moving_speed * cos(game->player.dir);
	*newY = game->player.y - game->player.moving_speed * sin(game->player.dir);
	if (game->map.map[(int)*newX][(int)*newY] == '1'
		|| game->map.map[(int)*newX][(int)*newY] == 'D')
		return (false);
	*newX = game->player.x + game->player.moving_speed * cos(game->player.dir
			- 45);
	*newY = game->player.y - game->player.moving_speed * sin(game->player.dir
			- 45);
	if (game->map.map[(int)*newX][(int)*newY] == '1'
		|| game->map.map[(int)*newX][(int)*newY] == 'D')
	{
		*newX = game->player.x + game->player.moving_speed
			* cos(game->player.dir + 45);
		*newY = game->player.y - game->player.moving_speed
			* sin(game->player.dir + 45);
		if (game->map.map[(int)*newX][(int)*newY] == '1'
			|| game->map.map[(int)*newX][(int)*newY] == 'D')
			return (false);
	}
	return (true);
}

bool	check_wall_collision(t_game *game, int keycode)
{
	int	new_x;
	int	new_y;

	if (keycode == W_BUTTON
		&& check_up_collision(game, &new_x, &new_y) == false)
		return (false);
	else if (keycode == S_BUTTON
		&& check_down_collision(game, &new_x, &new_y) == false)
		return (false);
	else if (keycode == A_BUTTON
		&& check_left_collision(game, &new_x, &new_y) == false)
		return (false);
	else if (keycode == D_BUTTON
		&& check_right_collision(game, &new_x, &new_y) == false)
		return (false);
	if (new_x < 0 || new_y < 0 || new_x >= game->map.rows
		|| new_y >= ft_strlen(game->map.map[(int)new_x]))
		return (false);
	if (game->map.map[(int)new_x][(int)new_y] == '1')
		return (false);
	return (true);
}
