/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:29:47 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/10 21:26:13 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_end_clean(char *str)
{
	if (!str)
		return (true);
	while (*str)
	{
		if (*str == ' ' || (*str >= 9 && *str <= 13))
			str++;
		else
			return (false);
	}
	return (true);
}

int	init(char *path, t_game *game)
{
	init_game(game);
	if (ft_path(path, game))
		free_all(1, game->gc);
	if (ft_parse_map(game))
		free_all(1, game->gc);
	if (check_map(game))
		free_all(1, game->gc);
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
	if (game->mlx.win)
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);
	close(game->map.fd);
	free_all(1, game->gc);
}

t_game	*get_game(int option, t_game *og_game)
{
	static t_game	*game;

	if (option == 1)
	{
		game = og_game;
		return (NULL);
	}
	else
		return (game);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (printf("Error\nInvalid number of arguments\n"));
	get_game(1, &game);
	if (init(av[1], &game))
	{
		free_game(&game);
		return (printf("Error\nParsing error\n"));
	}
	mlx_hook(game.mlx.win, 2, 0L, handle_press, &game);
	mlx_hook(game.mlx.win, 3, 0L, handle_release, &game);
	mlx_hook(game.mlx.win, 17, 0, quit, &game);
	mlx_loop_hook(game.mlx.mlx, simulate, &game);
	mlx_hook(game.mlx.win, ON_MOUSEMOVE, 0, handle_mouse, &game);
	mlx_loop(game.mlx.mlx);
	return (0);
}
