/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:29:47 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/09 22:50:19 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	init(char *path, t_game *game)
{
	init_game(game);
	if (ft_path(path, game))
		return (1);
	if (ft_parse_map(game))
		return (1);
	if (check_map(game))
		return (1);
	printf("done initing\n");
	return (0);
}

void	free_game(t_game *game)
{
	int	i;

	i = 0;
	if (game->walls.no.img)
		mlx_destroy_image(game->mlx.mlx, game->walls.no.img);
	if (game->walls.so.img)
		mlx_destroy_image(game->mlx.mlx, game->walls.so.img);
	if (game->walls.we.img)
		mlx_destroy_image(game->mlx.mlx, game->walls.we.img);
	if (game->walls.ea.img)
		mlx_destroy_image(game->mlx.mlx, game->walls.ea.img);
	if (game->minimap.img)
		mlx_destroy_image(game->mlx.mlx, game->minimap.img);
	if (game->sprites_image)
		mlx_destroy_image(game->mlx.mlx, game->sprites_image);
	if (game->mlx.win)
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);
	free_all(game->gc);
	close(game->map.fd);
}

bool	player_isnt_in_door(t_game *game)
{
	int	map_x;
	int	map_y;

	map_x = (int)game->player.y;
	map_y = (int)game->player.x;
	return (game->map.map[map_y][map_x] != 'D'
		&& game->map.map[map_y][map_x] != 'd');
}

int	handle_mouse_click(int button, int x, int y, void *param)
{
	t_game	*game;
	double	curr_dist;
	int		map_y;
	int		map_x;

	game = (t_game *)param;
	curr_dist = 0.0;
	y = x;
	if (button == 1 && player_isnt_in_door(game))
	{
		while (curr_dist <= 1.0)
		{
			map_y = game->player.x + (sin(game->player.dir) * curr_dist);
			map_x = game->player.y + (cos(game->player.dir) * curr_dist);
			if (handle_mouse_checks(game, map_x, map_y))
				return (1);
			else if (game->map.map[map_y][map_x] == '1')
				break ;
			curr_dist += 0.1;
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (printf("Error\nInvalid number of arguments\n"));
	if (init(av[1], &game))
		return (printf("Error\nParsing error\n"));
	mlx_hook(game.mlx.win, 2, 0L, handle_press, &game);
	mlx_hook(game.mlx.win, 3, 0L, handle_release, &game);
	mlx_hook(game.mlx.win, 17, 0, quite, &game);
	mlx_loop_hook(game.mlx.mlx, simulate, &game);
	mlx_hook(game.mlx.win, ON_MOUSEMOVE, 0, handle_mouse, &game);
	mlx_mouse_hook(game.mlx.win, handle_mouse_click, &game);
	mlx_loop(game.mlx.mlx);
	return (0);
}
