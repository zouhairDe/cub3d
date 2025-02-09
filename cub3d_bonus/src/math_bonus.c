/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:21:56 by mait-lah          #+#    #+#             */
/*   Updated: 2025/02/09 15:32:54 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

double	distance(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

double	deg_to_rad(double angle)
{
	return (angle * M_PI / 180.0);
}

double	rad_to_deg(double angle)
{
	return (angle * 180.0 / M_PI);
}

void	free_2d_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

bool	check_collor_values(char **side, int *r, int *g, int *b)
{
	*r = ft_atoi(side[0]);
	*g = ft_atoi(side[1]);
	*b = ft_atoi(side[2]);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (false);
	return (true);
}
