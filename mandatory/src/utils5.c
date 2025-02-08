/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:20:52 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/08 13:57:25 by zouddach         ###   ########.fr       */
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
	if (i > 0 && (j >= ft_strlen(map->map[i - 1])
			|| map->map[i - 1][j] == ' '))
		return (printf("Error\nMap has invalid gap above\n"));
	if (i < map->rows - 1 && (j >= ft_strlen(map->map[i + 1])
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
