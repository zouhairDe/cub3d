/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:20:49 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/08 13:00:38 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	game->mlx.data.addr = mlx_get_data_addr(game->mlx.data.img,
			&game->mlx.data.bits_per_pixel, &game->mlx.data.line_length,
			&game->mlx.data.endian);
	if (!game->mlx.data.addr)
		return (printf("Error\nCouldn't create image\n"));
	mlx_mouse_hide();
	return (0);
}

void	free_2d_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	convert_to_hex(t_game *game)
{
	char	**floor;
	char	**ceiling;
	int		r;
	int		g;
	int		b;

	floor = ft_split(game->map.floor, ',');
	ceiling = ft_split(game->map.ceiling, ',');
	if (!floor || two_d_arr_size(floor) != 3)
		return (printf("Error\nInvalid color format\n"));
	if (!ceiling || two_d_arr_size(ceiling) != 3)
		return (free_2d_arr(floor), printf("Error\nInvalid color format\n"));
	if (!check_collor_values(floor, &r, &g, &b) || !check_collor_values(ceiling,
			&r, &g, &b))
	{
		(free_2d_arr(floor), free_2d_arr(ceiling));
		return (printf("Error\nInvalid color values\n"));
	}
	game->walls.floor = rgb_to_hex(ft_atoi(floor[0]), ft_atoi(floor[1]),
			ft_atoi(floor[2]));
	game->walls.ceilling = rgb_to_hex(ft_atoi(ceiling[0]), ft_atoi(ceiling[1]),
			ft_atoi(ceiling[2]));
	free_2d_arr(floor);
	free_2d_arr(ceiling);
	return (0);
}

int	validate_elements(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->check_map.rows)
	{
		free(game->check_map.map[i]);
		i++;
	}
	if (!game->map.no || !game->map.so || !game->map.we || !game->map.ea
		|| !game->map.floor || !game->map.ceiling)
		return (printf("Error\nMissing required elements\n"));
	if (set_mlx(game))
		return (1);
	return (0);
}

char	*equalize_map_row(char *row, int max_length)
{
	char	*new_row;
	int		i;

	new_row = calloc(max_length + 1, sizeof(char));
	if (!new_row)
		return (NULL);
	i = 0;
	while (row[i] && i < max_length)
	{
		if (row[i] != ' ' && row[i] != '\t')
			new_row[i] = row[i];
		else
			new_row[i] = '0';
		i++;
	}
	while (i < max_length)
	{
		new_row[i] = '0';
		i++;
	}
	new_row[i] = '\0';
	return (new_row);
}
