/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:02:47 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/10 21:41:57 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_ignore_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

bool	is_all_data_valid(t_game *game)
{
	if (!game->map.no || !game->map.so || !game->map.we || !game->map.ea
		|| !game->map.floor || !game->map.ceiling)
		return (true);
	return (false);
}

int	not_surrounded(t_map *map)
{
	int	i;

	i = 0;
	if (ft_strchr(map->map[0], '*') || ft_strchr(map->map[map->rows - 1], '*'))
		return (printf("Error\nMap not surrounded by walls\n"));
	while (i < map->rows)
	{
		if ((map->map[i][ft_strlen(map->map[i]) - 1] == '*')
			|| (map->map[i][ft_ignore_space(map->map[i])] == '*'))
			return (printf("Error\nMap not surrounded by walls\n"));
		i++;
	}
	if (count_char(get_game(2, NULL)->map.floor, ',') > 2
		|| count_char(get_game(2, NULL)->map.ceiling, ',') > 2)
		return (printf("Error\nInvalid color format\n"));
	if (is_all_data_valid(get_game(2, NULL)))
		return (printf("Error\nmissing data\n"));
	return (0);
}

int	set_textures(t_game *game)
{
	game->map.no[ft_strlen(game->map.no) - 1] = 0;
	game->map.so[ft_strlen(game->map.so) - 1] = 0;
	game->map.we[ft_strlen(game->map.we) - 1] = 0;
	game->map.ea[ft_strlen(game->map.ea) - 1] = 0;
	game->walls.no.img = mlx_xpm_file_to_image(game->mlx.mlx, game->map.no,
			&game->walls.no.width, &game->walls.no.height);
	if (!game->walls.no.img)
		return (printf("Error\nCouldn't load NO texture\n"));
	game->walls.no.addr = mlx_get_data_addr(game->walls.no.img,
			&game->walls.no.bits_per_pixel, &game->walls.no.line_length,
			&game->walls.no.endian);
	game->walls.wt.img = mlx_xpm_file_to_image(game->mlx.mlx,
			"textures/WallTop.xpm", &game->walls.wt.width,
			&game->walls.wt.height);
	if (!game->walls.wt.img)
		return (printf("Error\nCouldn't load WT texture\n"));
	game->walls.wt.addr = mlx_get_data_addr(game->walls.wt.img,
			&game->walls.wt.bits_per_pixel, &game->walls.wt.line_length,
			&game->walls.wt.endian);
	game->walls.so.img = mlx_xpm_file_to_image(game->mlx.mlx, game->map.so,
			&game->walls.so.width, &game->walls.so.height);
	return (set_textures2(game));
}

int	quit(t_game *game)
{
	if (game->walls.no.img)
		mlx_destroy_image(game->mlx.mlx, game->walls.no.img);
	if (game->walls.so.img)
		mlx_destroy_image(game->mlx.mlx, game->walls.so.img);
	if (game->walls.we.img)
		mlx_destroy_image(game->mlx.mlx, game->walls.we.img);
	if (game->walls.ea.img)
		mlx_destroy_image(game->mlx.mlx, game->walls.ea.img);
	if (game->walls.wt.img)
		mlx_destroy_image(game->mlx.mlx, game->walls.wt.img);
	free_all(0, game->gc);
	return (0);
}
