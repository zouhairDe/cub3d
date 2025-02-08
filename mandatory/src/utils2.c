/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:36:22 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/08 13:19:08 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_game_map(t_map *map)
{
	map->fd = 0;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->wt = NULL;
	map->ceiling = NULL;
	map->floor = NULL;
	map->map = NULL;
	map->rows = 0;
	map->max_cols = 0;
}

void	init_walls(t_texture *walls)
{
	walls->no.img = NULL;
	walls->no.addr = NULL;
	walls->so.img = NULL;
	walls->so.addr = NULL;
	walls->we.img = NULL;
	walls->we.addr = NULL;
	walls->ea.img = NULL;
	walls->ea.addr = NULL;
	walls->wt.img = NULL;
	walls->wt.addr = NULL;
	walls->ceilling = 0;
	walls->floor = 0;
}

void	init_game(t_game *game)
{
	init_game_map(&game->map);
	init_game_map(&game->check_map);
	game->player.x = 0.0;
	game->player.y = 0.0;
	game->player.dir = 0;
	game->player.fov = 0;
	game->player.moving_speed = 0.1;
	game->player.rotation_speed = 0.1;
	game->mlx.mlx = NULL;
	game->mlx.win = NULL;
	game->setting.width = 0;
	game->setting.height = 0;
	game->setting.title = NULL;
	game->setting.player_speed = 1;
	game->setting.mlx.mlx = NULL;
	game->setting.mlx.win = NULL;
	game->mouse = false;
	game->mouse_x = WINDOW_WIDTH / 2;
	game->mouse_y = WINDOW_HEIGHT / 2;
	game->crosshair.size = 4;
	game->crosshair.thickness = 2;
	game->frame = 0;
	game->gc = NULL;
	init_walls(&game->walls);
}

int	ft_parse_map(t_game *game)
{
	char	*line;
	char	*tmp;

	(void)tmp;
	line = get_next_line(game->map.fd);
	while (line)
	{
		if (manage_line_logic(line, game))
			return (1);
		free(line);
		line = get_next_line(game->map.fd);
	}
	return (0);
}

int	ft_path(char *path, t_game *game)
{
	int	dot;

	dot = path - ft_strrchr(path, '.');
	if (dot == 0 || !ft_strncmp(&path[dot], ".cub", 4))
		return (printf("Error\nInvalid file extension\n"));
	game->map.fd = open(path, O_RDONLY);
	if (game->map.fd == -1)
		return (printf("Error\nFile not found\n"));
	return (0);
}
