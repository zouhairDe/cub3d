/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:02:47 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/10 14:20:19 by zouddach         ###   ########.fr       */
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
	free_all(game->gc);
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
	printf("Exiting\n");
	close(game->map.fd);
	exit(0);
	return (0);
}

bool	check_collor_values(char **side, int *r, int *g, int *b)
{
	*r = ft_atoi2(side[0]);
	*g = ft_atoi2(side[1]);
	*b = ft_atoi2(side[2]);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (false);
	return (true);
}
