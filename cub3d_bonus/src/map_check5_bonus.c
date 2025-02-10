/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check5_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:37:39 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/10 21:26:13 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	init_sprites(char **f1, char **f2, char **f3, char **f4)
{
	*f1 = "textures/hand/hand1.xpm";
	*f2 = "textures/hand/hand2.xpm";
	*f3 = "textures/hand/hand3.xpm";
	*f4 = "textures/hand/hand4.xpm";
}

void	get_sprites(t_game *game, char *f, bool onRelease)
{
	if (onRelease)
		game->sprites_index = 0;
	game->sprites_image = mlx_xpm_file_to_image(game->mlx.mlx, f,
			&game->mlx.data.width, &game->mlx.data.height);
	return ;
}

bool	check_wall_collision(t_game *game, int keycode)
{
	int	new_x;
	int	new_y;

	if (keycode == W_BUTTON && !check_up_collision(game, &new_x, &new_y))
		return (false);
	else if (keycode == S_BUTTON && !check_down_collision(game, &new_x, &new_y))
		return (false);
	else if (keycode == A_BUTTON && !check_left_collision(game, &new_x, &new_y))
		return (false);
	else if (keycode == D_BUTTON && !check_right_collision(game, &new_x,
			&new_y))
		return (false);
	if (new_x < 0 || new_y < 0 || new_x >= game->map.rows
		|| (size_t)new_y >= ft_strlen(game->map.map[(int)new_x]))
		return (false);
	if (game->map.map[(int)new_x][(int)new_y] == '1'
		|| game->map.map[(int)new_x][(int)new_y] == 'D')
		return (false);
	return (true);
}

void	sprites(t_game *game, bool onRelease)
{
	char	*f1;
	char	*f2;
	char	*f3;
	char	*f4;

	init_sprites(&f1, &f2, &f3, &f4);
	if (game->sprites_index == 0 || game->sprites_index == 8)
		get_sprites(game, f1, onRelease);
	else if (game->sprites_index == 1 || game->sprites_index == 7)
		get_sprites(game, f2, onRelease);
	else if (game->sprites_index == 2 || game->sprites_index == 6)
		get_sprites(game, f3, onRelease);
	else if (game->sprites_index == 3 || game->sprites_index == 5)
		get_sprites(game, f4, onRelease);
	else if (game->sprites_index == 4)
		get_sprites(game, "textures/hand/hand5.xpm", onRelease);
	if (onRelease)
		get_sprites(game, f1, onRelease);
	game->sprites_index++;
	if (game->sprites_index == 9)
		game->sprites_index = 1;
	if (!game->sprites_image)
		free_all(1, game->gc);
}

int	handle_press2(t_game *game, int keycode)
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
	else
		return (0);
	return (1);
}
