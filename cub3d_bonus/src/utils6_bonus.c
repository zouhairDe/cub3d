/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:51:25 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/10 21:38:43 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

bool	is_end_clean(char *str)
{
	if (!str)
		return (true);
	while (*str)
	{
		if (*str == ' ' || (*str >= 9 && *str <= 13))
			str++;
		else
			return (false);
	}
	return (true);
}

size_t	ft_atoi2(char *str)
{
	size_t	i;
	size_t	sign;
	size_t	res;

	sign = 1;
	res = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = (10 * res) + (str[i] - '0') * sign;
		i++;
	}
	if (res > 2147483647 || res < 0 || !is_end_clean(str + i))
		return (-1);
	return (res);
}

int	ft_ignore_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
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
