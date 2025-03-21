/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:36:22 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/10 21:41:44 by mait-lah         ###   ########.fr       */
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
	map->map_done = false;
	map->map_started = false;
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
	walls->ceilling = -1;
	walls->floor = -1;
}

void	init_game(t_game *game)
{
	init_game_map(&game->map);
	init_game_map(&game->check_map);
	game->player.x = 0.0;
	game->player.y = 0.0;
	game->player.dir = 0;
	game->player.fov = 0;
	game->player.moving_speed = 0.15;
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

int	ft_is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

int	ft_parse_map(t_game *game)
{
	char	*line;
	char	*tmp;

	(void)tmp;
	line = get_next_line(game->map.fd);
	while (line)
	{
		if (game->map.map_done)
		{
			if (ft_is_empty_line(line))
			{
				free_ptr(get_game(2, NULL), line);
				line = get_next_line(game->map.fd);
				continue ;
			}
			else
				return (printf("Error\nInvalid content in map\n"));
		}
		if (manage_line_logic(line, game))
			return (1);
		free_ptr(get_game(2, NULL), line);
		line = get_next_line(game->map.fd);
	}
	return (0);
}
