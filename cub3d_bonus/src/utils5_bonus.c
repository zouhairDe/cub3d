/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:13:15 by mait-lah          #+#    #+#             */
/*   Updated: 2025/02/10 13:57:48 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

unsigned int	rgb_to_hex(int r, int g, int b)
{
	unsigned int	color;

	color = 0;
	color |= r << 16;
	color |= g << 8;
	color |= b;
	return (color);
}

int	two_d_arr_size(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

void	ft_cut_char(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}

int	count_char(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	handle_mouse_checks(t_game *game, int map_x, int map_y)
{
	if (map_x < 0 || map_y < 0 || map_x >= game->map.max_cols
		|| map_y >= game->map.rows)
		return (printf("out of bounds\n"));
	if (game->map.map[map_y][map_x] == 'D')
	{
		game->map.map[map_y][map_x] = 'd';
		return (printf("door opened at %d,%d\n", map_x, map_y));
	}
	else if (game->map.map[map_y][map_x] == 'd')
	{
		game->map.map[map_y][map_x] = 'D';
		return (printf("door closed at %d,%d\n", map_x, map_y));
	}
	return (0);
}
