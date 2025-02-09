/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:21:27 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/09 14:52:49 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

bool	check_up_collision(t_game *game, int *new_x, int *new_y)
{
	*new_x = game->player.x + game->player.moving_speed * sin(game->player.dir);
	*new_y = game->player.y + game->player.moving_speed * cos(game->player.dir);
	if (*new_x < 0 || *new_y < 0 || *new_x >= game->map.rows
		|| *new_y >= ft_strlen(game->map.map[(int)*new_x]))
		return (false);
	if (game->map.map[(int)*new_x][(int)*new_y] == '1'
		|| game->map.map[(int)*new_x][(int)*new_y] == 'D')
		return (false);
	*new_x = game->player.x + game->player.moving_speed * sin(game->player.dir
			- 45);
	*new_y = game->player.y + game->player.moving_speed * cos(game->player.dir
			- 45);
	if (game->map.map[(int)*new_x][(int)*new_y] == '1'
		|| game->map.map[(int)*new_x][(int)*new_y] == 'D')
	{
		*new_x = game->player.x + game->player.moving_speed
			* sin(game->player.dir + 45);
		*new_y = game->player.y + game->player.moving_speed
			* cos(game->player.dir + 45);
		if (game->map.map[(int)*new_x][(int)*new_y] == '1'
			|| game->map.map[(int)*new_x][(int)*new_y] == 'D')
			return (false);
	}
	return (true);
}

bool	check_down_collision(t_game *game, int *new_x, int *new_y)
{
	*new_x = game->player.x - game->player.moving_speed * sin(game->player.dir);
	*new_y = game->player.y - game->player.moving_speed * cos(game->player.dir);
	if (*new_x < 0 || *new_y < 0 || *new_x >= game->map.rows
		|| *new_y >= ft_strlen(game->map.map[(int)*new_x]))
		return (false);
	if (game->map.map[(int)*new_x][(int)*new_y] == '1'
		|| game->map.map[(int)*new_x][(int)*new_y] == 'D')
		return (false);
	*new_x = game->player.x - game->player.moving_speed * sin(game->player.dir
			- 45);
	*new_y = game->player.y - game->player.moving_speed * cos(game->player.dir
			- 45);
	if (game->map.map[(int)*new_x][(int)*new_y] == '1'
		|| game->map.map[(int)*new_x][(int)*new_y] == 'D')
	{
		*new_x = game->player.x - game->player.moving_speed
			* sin(game->player.dir + 45);
		*new_y = game->player.y - game->player.moving_speed
			* cos(game->player.dir + 45);
		if (game->map.map[(int)*new_x][(int)*new_y] == '1'
			|| game->map.map[(int)*new_x][(int)*new_y] == 'D')
			return (false);
	}
	return (true);
}

bool	check_left_collision(t_game *game, int *new_x, int *new_y)
{
	*new_y = game->player.x - game->player.moving_speed * cos(game->player.dir);
	*new_y = game->player.y + game->player.moving_speed * sin(game->player.dir);
	if (*new_x < 0 || *new_y < 0 || *new_x >= game->map.rows
		|| *new_y >= ft_strlen(game->map.map[(int)*new_x]))
		return (false);
	if (game->map.map[(int)*new_y][(int)*new_y] == '1'
		|| game->map.map[(int)*new_y][(int)*new_y] == 'D')
		return (false);
	*new_y = game->player.x - game->player.moving_speed * sin(game->player.dir);
	*new_y = game->player.y + game->player.moving_speed * cos(game->player.dir);
	if (game->map.map[(int)*new_y][(int)*new_y] == '1'
		|| game->map.map[(int)*new_y][(int)*new_y] == 'D')
	{
		*new_y = game->player.x - game->player.moving_speed
			* sin(game->player.dir + 90);
		*new_y = game->player.y + game->player.moving_speed
			* cos(game->player.dir + 90);
		if (game->map.map[(int)*new_y][(int)*new_y] == '1'
			|| game->map.map[(int)*new_y][(int)*new_y] == 'D')
			return (false);
	}
	return (true);
}

bool	check_right_collision(t_game *game, int *new_x, int *new_y)
{
	*new_x = game->player.x + game->player.moving_speed * cos(game->player.dir);
	*new_y = game->player.y - game->player.moving_speed * sin(game->player.dir);
	if (*new_x < 0 || *new_y < 0 || *new_x >= game->map.rows
		|| *new_y >= ft_strlen(game->map.map[(int)*new_x]))
		return (false);
	if (game->map.map[(int)*new_x][(int)*new_y] == '1'
		|| game->map.map[(int)*new_x][(int)*new_y] == 'D')
		return (false);
	*new_x = game->player.x + game->player.moving_speed * sin(game->player.dir
			- 90);
	*new_y = game->player.y - game->player.moving_speed * cos(game->player.dir
			- 90);
	if (game->map.map[(int)*new_x][(int)*new_y] == '1'
		|| game->map.map[(int)*new_x][(int)*new_y] == 'D')
	{
		*new_x = game->player.x + game->player.moving_speed
			* sin(game->player.dir);
		*new_y = game->player.y - game->player.moving_speed
			* cos(game->player.dir);
		if (game->map.map[(int)*new_x][(int)*new_y] == '1'
			|| game->map.map[(int)*new_x][(int)*new_y] == 'D')
			return (false);
	}
	return (true);
}
