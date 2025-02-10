/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check1_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 04:48:13 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/10 02:50:29 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	handle_press(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == 53)
		return (quit(param));
	if (keycode == H_BUTTON)
		game->mouse = !game->mouse;
	if (keycode == H_BUTTON && game->mouse)
		mlx_mouse_show();
	else if (keycode == H_BUTTON && !game->mouse)
		mlx_mouse_hide();
	else if (keycode == LEFT_BUTTON)
		game->player.dir -= game->player.rotation_speed;
	else if (keycode == RIGHT_BUTTON)
		game->player.dir += game->player.rotation_speed;
	else if (!handle_press2(game, keycode))
		return (1);
	game->player.dir = normalize_angle(game->player.dir);
	sprites(game, false);
	return (0);
}

int	handle_release(int keycode, void *param)
{
	t_game	*game;

	(void)keycode;
	game = (t_game *)param;
	sprites(game, true);
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

int	set_mlx(t_game *game)
{
	game->mlx.mlx = mlx_init();
	if (!game->mlx.mlx)
		return (printf("Error\nCouldn't initialize mlx\n"));
	game->mlx.win = mlx_new_window(game->mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"Cub3D");
	if (!game->mlx.win)
		return (printf("Error\nCouldn't create window\n"));
	game->mlx.data.img = mlx_new_image(game->mlx.mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT);
	if (!game->mlx.data.img)
		return (printf("Error\nCouldn't create image\n"));
	game->minimap.img = mlx_new_image(game->mlx.mlx, MINIMAP_WIDTH,
			MINIMAP_HEIGHT);
	if (!game->minimap.img)
		return (printf("Error\nCouldn't create image\n"));
	game->mlx.data.addr = mlx_get_data_addr(game->mlx.data.img,
			&game->mlx.data.bits_per_pixel, &game->mlx.data.line_length,
			&game->mlx.data.endian);
	if (!game->mlx.data.addr)
		return (printf("Error\nCouldn't create image\n"));
	mlx_mouse_hide();
	return (0);
}

int	check_map(t_game *game)
{
	if (copy_map(game))
		return (1);
	game->map.map = equalize_map(game->map.map, game->map.rows);
	if (!game->map.map)
		return (1);
	if (check_chars(&game->check_map))
		return (1);
	if (check_map_border(&game->check_map))
		return (1);
	if (set_player(game))
		return (1);
	floodfill(&game->check_map, 5, 13);
	if (not_surrounded(&game->check_map))
		return (1);
	if (convert_to_hex(game))
		return (1);
	if (validate_elements(game))
		return (1);
	if (game->map.no == NULL || game->map.so == NULL || game->map.we == NULL
		|| game->map.ea == NULL)
		return (printf("Error\nMissing texture path\n"));
	if (set_textures(game))
		return (1);
	sprites(game, false);
	return (0);
}
