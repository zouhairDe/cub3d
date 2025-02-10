/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:42:15 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/10 21:42:19 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	start_map_allocation(t_game *game, char **line)
{
	char	**tmp;
	int		i;

	i = -1;
	game->map.map_started = true;
	tmp = game->map.map;
	game->map.map = g_malloc(game, sizeof(char *) * (game->map.rows + 1));
	if (!game->map.map)
		free_all(1, game->gc);
	while (++i < game->map.rows)
		game->map.map[i] = tmp[i];
	game->map.map[i] = ft_strdup(*line);
	game->map.rows++;
	if (game->map.max_cols < (int)ft_strlen(*line))
		game->map.max_cols = ft_strlen(*line) - 1;
	if (!game->map.map[i])
		return (1);
	ft_cut_char(game->map.map[i], '\n');
	free_ptr(game, tmp);
	tmp = NULL;
	return (0);
}

int	manage_line_logic(char *line, t_game *game)
{
	char	*tmp;

	tmp = line;
	dump_spaces(&line);
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "NO\t", 3))
		return (ft_line_value(line, &game->map.no));
	else if (!ft_strncmp(line, "SO ", 3) || !ft_strncmp(line, "SO\t", 3))
		return (ft_line_value(line, &game->map.so));
	else if (!ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "WE\t", 3))
		return (ft_line_value(line, &game->map.we));
	else if (!ft_strncmp(line, "EA ", 3) || !ft_strncmp(line, "EA\t", 3))
		return (ft_line_value(line, &game->map.ea));
	else if (!ft_strncmp(line, "C ", 2) || !ft_strncmp(line, "C\t", 2))
		return (ft_line_value(line, &game->map.ceiling));
	else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "F\t", 2))
		return (ft_line_value(line, &game->map.floor));
	else if (ft_strchr(line, '1') || ft_strchr(line, '0'))
		return (start_map_allocation(game, &tmp));
	else if (game->map.map_started && line[0] == '\n')
		game->map.map_done = true;
	else if (game->map.map_started)
		return (printf("Error\nInvalid content in map file\n")
			, free_all(1, game->gc), 1);
	return (0);
}

void	put_player(t_game *game, int i)
{
	game->player.x = i + 0.5;
	if (ft_find(game->check_map.map[i], 'S') != -1)
	{
		game->player.dir = deg_to_rad(270);
		game->player.y = ft_find(game->check_map.map[i], 'S') + 0.5;
	}
	else if (ft_find(game->check_map.map[i], 'W') != -1)
	{
		game->player.dir = deg_to_rad(180);
		game->player.y = ft_find(game->check_map.map[i], 'W') + 0.5;
	}
	else if (ft_find(game->check_map.map[i], 'N') != -1)
	{
		game->player.dir = deg_to_rad(90);
		game->player.y = ft_find(game->check_map.map[i], 'N') + 0.5;
	}
	else
	{
		game->player.dir = deg_to_rad(0);
		game->player.y = ft_find(game->check_map.map[i], 'E') + 0.5;
	}
}

int	set_textures2(t_game *game)
{
	if (!game->walls.so.img)
		return (printf("Error\nCouldn't load SO texture\n"));
	game->walls.so.addr = mlx_get_data_addr(game->walls.so.img,
			&game->walls.so.bits_per_pixel, &game->walls.so.line_length,
			&game->walls.so.endian);
	game->walls.we.img = mlx_xpm_file_to_image(game->mlx.mlx, game->map.we,
			&game->walls.we.width, &game->walls.we.height);
	if (!game->walls.we.img)
		return (printf("Error\nCouldn't load WE texture\n"));
	game->walls.we.addr = mlx_get_data_addr(game->walls.we.img,
			&game->walls.we.bits_per_pixel, &game->walls.we.line_length,
			&game->walls.we.endian);
	game->walls.ea.img = mlx_xpm_file_to_image(game->mlx.mlx, game->map.ea,
			&game->walls.ea.width, &game->walls.ea.height);
	if (!game->walls.ea.img)
		return (printf("Error\nCouldn't load EA texture\n"));
	game->walls.ea.addr = mlx_get_data_addr(game->walls.ea.img,
			&game->walls.ea.bits_per_pixel, &game->walls.ea.line_length,
			&game->walls.ea.endian);
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
