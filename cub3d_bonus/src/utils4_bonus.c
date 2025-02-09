/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 05:35:33 by mait-lah          #+#    #+#             */
/*   Updated: 2025/02/09 05:35:35 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	is_wall(t_game *game, double pX, double pY)
{
	if (pX <= 0 || pX >= game->map.max_cols || pY <= 0 || pY >= game->map.rows)
		return (true);
	return ((game->map.map[(int)(pY)][(int)(pX)] == '1'));
}

double	normalize_angle(double angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

void	collor_ceilling(t_game *game)
{
	int		i;
	int		j;
	bool	toggle;

	toggle = false;
	i = 0;
	while (i++ < WINDOW_WIDTH)
	{
		j = 0;
		while (j++ < WINDOW_HEIGHT / 2)
			my_mlx_pixel_put(&game->mlx.data, i, j, game->walls.ceilling);
	}
}

void	collor_floor(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		j = WINDOW_HEIGHT / 2;
		while (j < WINDOW_HEIGHT)
		{
			my_mlx_pixel_put(&game->mlx.data, i, j, game->walls.floor);
			j++;
		}
		i++;
	}
}