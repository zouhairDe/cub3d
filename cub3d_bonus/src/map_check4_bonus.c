/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check4_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:09:52 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/09 15:32:25 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	ft_ignore_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

int	not_surrounded(t_map *map)
{
	int	i;
	int	j;

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
	return (0);
}

int	set_textures3(t_game *game)
{
	if (!game->walls.ea.img)
		return (printf("Error\nCouldn't load EA texture\n"));
	game->walls.ea.addr = mlx_get_data_addr(game->walls.ea.img,
			&game->walls.ea.bits_per_pixel, &game->walls.ea.line_length,
			&game->walls.ea.endian);
	game->walls.closed_door.img = mlx_xpm_file_to_image(game->mlx.mlx,
			"textures/spruce_door_bottom.xpm", &game->walls.closed_door.width,
			&game->walls.closed_door.height);
	if (!game->walls.closed_door.img)
		return (printf("Error\nCouldn't load closed_door texture\n"));
	game->walls.closed_door.addr = mlx_get_data_addr(
			game->walls.closed_door.img,
			&game->walls.closed_door.bits_per_pixel,
			&game->walls.closed_door.line_length,
			&game->walls.closed_door.endian);
	return (0);
}

int	set_textures(t_game *game)
{
	game->map.no[ft_strlen(game->map.no) - 1] = 0;
	game->map.so[ft_strlen(game->map.so) - 1] = 0;
	game->map.we[ft_strlen(game->map.we) - 1] = 0;
	game->map.ea[ft_strlen(game->map.ea) - 1] = 0;
	game->minimap.img = mlx_new_image(game->mlx.mlx, 32 * 8, 32 * 8);
	if (!game->minimap.img)
		return (printf("Error\nCouldn't create MINIMAP image\n"));
	game->minimap.addr = mlx_get_data_addr(game->minimap.img,
			&game->minimap.bits_per_pixel, &game->minimap.line_length,
			&game->minimap.endian);
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
	if (set_textures2(game))
		return (1);
	if (set_textures3(game))
		return (1);
	return (0);
}

int	quite(t_game *game)
{
	if (game->minimap.img)
		mlx_destroy_image(game->mlx.mlx, game->minimap.img);
	if (game->walls.no.img)
		mlx_destroy_image(game->mlx.mlx, game->walls.no.img);
	if (game->walls.so.img)
		mlx_destroy_image(game->mlx.mlx, game->walls.so.img);
	if (game->walls.we.img)
		mlx_destroy_image(game->mlx.mlx, game->walls.we.img);
	if (game->walls.ea.img)
		mlx_destroy_image(game->mlx.mlx, game->walls.ea.img);
	if (game->walls.closed_door.img)
		mlx_destroy_image(game->mlx.mlx, game->walls.closed_door.img);
	free_all(game->gc);
	close(game->map.fd);
	printf("Exiting\n");
	exit(0);
	return (0);
}
