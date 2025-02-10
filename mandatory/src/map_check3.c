/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:10:06 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/10 07:27:07 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	check_up_collision(t_game *game, int *new_x, int *new_y)
{
	double	start;
	double	idx;

	start = game->player.moving_speed + 0.1;
	idx = 0;
	*new_x = game->player.x + start * sin(game->player.dir);
	*new_y = game->player.y + start * cos(game->player.dir);
	if (*new_x < 0 || *new_y < 0 || *new_x >= game->map.rows
		|| (size_t)(*new_y) >= ft_strlen(game->map.map[(int)*new_x]))
		return (false);
	if (game->map.map[(int)*new_x][(int)*new_y] == '1'
		|| game->map.map[(int)*new_x][(int)*new_y] == 'D')
		return (false);
	while (idx < game->player.moving_speed)
	{
		*new_x = game->player.x + (start + idx) * sin(game->player.dir);
		*new_y = game->player.y + (start + idx) * cos(game->player.dir);
		if (game->map.map[(int)*new_x][(int)*new_y] == '1'
			|| game->map.map[(int)*new_x][(int)*new_y] == 'D')
			return (false);
		idx += 0.001;
	}
	return (true);
}

bool	check_left_collision(t_game *game, int *new_x, int *new_y)
{
	double	start;
	double	idx;

	idx = 0;
	start = game->player.moving_speed + 0.1;
	*new_x = game->player.x - start * cos(game->player.dir);
	*new_y = game->player.y + start * sin(game->player.dir);
	if (*new_x < 0 || *new_y < 0 || *new_x >= game->map.rows
		|| (size_t)(*new_y) >= ft_strlen(game->map.map[(int)*new_x]))
		return (false);
	if (game->map.map[(int)*new_x][(int)*new_y] == '1'
		|| game->map.map[(int)*new_x][(int)*new_y] == 'D')
		return (false);
	while (idx < game->player.moving_speed)
	{
		*new_x = game->player.x - (start + idx) * cos(game->player.dir);
		*new_y = game->player.y + (start + idx) * sin(game->player.dir);
		if (game->map.map[(int)*new_x][(int)*new_y] == '1'
			|| game->map.map[(int)*new_x][(int)*new_y] == 'D')
			return (false);
		idx += 0.001;
	}
	return (true);
}

bool	check_down_collision(t_game *game, int *new_x, int *new_y)
{
	double	start;
	double	idx;

	idx = 0;
	start = game->player.moving_speed + 0.1;
	*new_x = game->player.x - start * sin(game->player.dir);
	*new_y = game->player.y - start * cos(game->player.dir);
	if (*new_x < 0 || *new_y < 0 || *new_x >= game->map.rows
		|| (size_t)(*new_y) >= ft_strlen(game->map.map[(int)*new_x]))
		return (false);
	if (game->map.map[(int)*new_x][(int)*new_y] == '1'
		|| game->map.map[(int)*new_x][(int)*new_y] == 'D')
		return (false);
	while (idx < game->player.moving_speed)
	{
		*new_x = game->player.x - (start + idx) * sin(game->player.dir);
		*new_y = game->player.y - (start + idx) * cos(game->player.dir);
		if (game->map.map[(int)*new_x][(int)*new_y] == '1'
			|| game->map.map[(int)*new_x][(int)*new_y] == 'D')
			return (false);
		idx += 0.001;
	}
	return (true);
}

bool	check_right_collision(t_game *game, int *new_x, int *new_y)
{
	double	start;
	double	idx;

	idx = 0;
	start = game->player.moving_speed + 0.1;
	*new_x = game->player.x + start * cos(game->player.dir);
	*new_y = game->player.y - start * sin(game->player.dir);
	if (*new_x < 0 || *new_y < 0 || *new_x >= game->map.rows
		|| (size_t)(*new_y) >= ft_strlen(game->map.map[(int)*new_x]))
		return (false);
	if (game->map.map[(int)*new_x][(int)*new_y] == '1'
		|| game->map.map[(int)*new_x][(int)*new_y] == 'D')
		return (false);
	while (idx < game->player.moving_speed)
	{
		*new_x = game->player.x + (start + idx) * cos(game->player.dir);
		*new_y = game->player.y - (start + idx) * sin(game->player.dir);
		if (game->map.map[(int)*new_x][(int)*new_y] == '1'
			|| game->map.map[(int)*new_x][(int)*new_y] == 'D')
			return (false);
		idx += 0.001;
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
		|| (size_t)new_y >= ft_strlen(game->map.map[(int)new_x]))
		return (false);
	if (game->map.map[(int)new_x][(int)new_y] == '1')
		return (false);
	return (true);
}
