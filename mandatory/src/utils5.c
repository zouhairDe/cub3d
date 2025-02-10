/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:20:52 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/10 13:56:34 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_replace(char *str, char c, char *news)
{
	int		i;
	int		c_count;
	char	*res;
	char	*original_str;

	if (!str)
		return (NULL);
	c_count = count_char(str, c);
	if (c_count == 0)
		return (str);
	i = 0;
	res = malloc(ft_strlen(str) + (ft_strlen(news) * c_count) + 1);
	if (!res)
		return (NULL);
	original_str = str;
	while (*str)
	{
		if (*str == c)
			(ft_strlcpy(&res[i], news, ft_strlen(news) + 1),
				i += ft_strlen(news));
		else
			res[i++] = *str;
		str++;
	}
	return (res[i] = '\0', free(original_str), res);
}

int	dump_spaces(char **line)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
	if (**line == '\0')
		return (1);
	return (0);
}

int	check_map_boundaries(t_map *map, int i, int j, int len)

{
	if (i == 0 || i == map->rows - 1 || j == 0 || j == len - 1)
		return (printf("Error\nMap not properly enclosed\n"));
	if (i > 0 && ((size_t)j >= ft_strlen(map->map[i - 1])
			|| map->map[i - 1][j] == ' '))
		return (printf("Error\nMap has invalid gap above\n"));
	if (i < map->rows - 1 && ((size_t)j >= ft_strlen(map->map[i + 1])
			|| map->map[i + 1][j] == ' '))
		return (printf("Error\nMap has invalid gap below\n"));
	if (j > 0 && map->map[i][j - 1] == ' ')
		return (printf("Error\nMap has invalid gap to the left\n"));
	if (j < len - 1 && map->map[i][j + 1] == ' ')
		return (printf("Error\nMap has invalid gap to the right\n"));
	return (0);
}

int	check_map_border(t_map *map)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		len = ft_strlen(map->map[i]);
		while (++j < len)
		{
			if (map->map[i][j] == '0' || map->map[i][j] == 'N'
				|| map->map[i][j] == 'S' || map->map[i][j] == 'E'
				|| map->map[i][j] == 'W')
			{
				if (check_map_boundaries(map, i, j, len) == -1)
					return (-1);
			}
		}
	}
	return (0);
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
