/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check6_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:21:00 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/10 13:57:40 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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
	game->walls.floor = rgb_to_hex(ft_atoi2(floor[0]),
			ft_atoi2(floor[1]), ft_atoi2(floor[2]));
	game->walls.ceilling = rgb_to_hex(ft_atoi2(ceiling[0]),
			ft_atoi2(ceiling[1]), ft_atoi2(ceiling[2]));
	free_2d_arr(floor);
	free_2d_arr(ceiling);
	return (0);
}

char	*equalize_map_row(const char *row, int max_length)
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

int	start_map_equalization(char **new_map, char **map, int row_count,
		int max_length)
{
	int	i;

	i = -1;
	while (++i < row_count)
	{
		new_map[i] = equalize_map_row(map[i], max_length);
		if (!new_map[i])
		{
			while (--i >= 0)
				free(new_map[i]);
			free(new_map);
			return (-1);
		}
	}
	new_map[row_count] = NULL;
	return (0);
}

char	**equalize_map(char **map, int row_count)
{
	char	**new_map;
	int		max_length;
	int		len;
	int		i;

	if (!map || row_count <= 0)
		return (NULL);
	max_length = 0;
	i = -1;
	while (++i < row_count)
	{
		len = strlen(map[i]);
		if (len > max_length)
			max_length = len;
	}
	new_map = malloc((row_count + 1) * sizeof(char *));
	if (!new_map)
		return (NULL);
	if (start_map_equalization(new_map, map, row_count, max_length) == -1)
		return (NULL);
	i = -1;
	while (++i < row_count)
		free(map[i]);
	return (new_map);
}

int	validate_elements(t_game *game)
{
	int	i;

	if (!game->map.no || !game->map.so || !game->map.we || !game->map.ea
		|| !game->map.floor || !game->map.ceiling)
		return (printf("Error\nMissing required elements\n"));
	if (set_mlx(game))
		return (1);
	i = -1;
	while (++i < game->check_map.rows)
		free(game->check_map.map[i]);
	return (0);
}
