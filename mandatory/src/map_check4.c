/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:20:49 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/10 17:52:59 by zouddach         ###   ########.fr       */
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
	if (!arr)
		return ;
	while (arr[i])
	{
		if (arr[i])
			free_ptr(get_game(2, NULL), arr[i]);
		i++;
	}
	free_ptr(get_game(2, NULL), arr);
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
	game->walls.floor = rgb_to_hex(ft_atoi2(floor[0]), ft_atoi2(floor[1]),
			ft_atoi2(floor[2]));
	game->walls.ceilling = rgb_to_hex(ft_atoi2(ceiling[0]),
			ft_atoi2(ceiling[1]), ft_atoi2(ceiling[2]));
	free_2d_arr(floor);
	free_2d_arr(ceiling);
	return (0);
}

int	validate_elements(t_game *game)
{
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

	new_row = g_malloc(get_game(2, NULL), max_length + 1);
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
