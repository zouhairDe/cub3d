/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 04:45:13 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/02 02:46:24 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return;
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int rgb_to_hex(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

int two_d_arr_size(char **arr)
{
	int i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

void ft_cut_char(char *str, char c)
{
	int i;
	int j;

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

int count_char(char *str, char c)
{
	int i;
	int count;

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

char *ft_replace(char *str, char c, char *news)
{
	int i;
	int c_count;
	char *res;
	char *original_str;

	if (!str || !news)
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
		{
			ft_strlcpy(&res[i], news, ft_strlen(news) + 1);
			i += ft_strlen(news);
		}
		else
			res[i++] = *str;
		str++;
	}
	res[i] = '\0';
	free(original_str);
	return (res);
}

int dump_spaces(char **line)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
	if (**line == '\0')
		return (1);
	return (0);
}

int check_map_border(t_map *map)
{
    int i;
    int j;
    int len;

	i = -1;
    while (++i < map->rows)
    {
        j = -1;
        len = ft_strlen(map->map[i]);
        while (++j < len)
        {
            if (map->map[i][j] == '0' || 
                map->map[i][j] == 'N' || 
                map->map[i][j] == 'S' || 
                map->map[i][j] == 'E' || 
                map->map[i][j] == 'W')
            {
                if (i == 0 || i == map->rows - 1 || j == 0 || j == len - 1)
                    return (printf("Error\nMap not properly enclosed\n"));
                if (i > 0 && (j >= ft_strlen(map->map[i - 1]) || map->map[i - 1][j] == ' '))
                    return (printf("Error\nMap has invalid gap above\n"));
                if (i < map->rows - 1 && (j >= ft_strlen(map->map[i + 1]) || map->map[i + 1][j] == ' '))
                    return (printf("Error\nMap has invalid gap below\n"));
                if (j > 0 && map->map[i][j - 1] == ' ')
                    return (printf("Error\nMap has invalid gap to the left\n"));
                if (j < len - 1 && map->map[i][j + 1] == ' ')
                    return (printf("Error\nMap has invalid gap to the right\n"));
            }
        }
    }
    return (0);
}

int ft_line_value(char *line, char **value)
{
    while (*line && (*line == ' ' || *line == '\t'))
        line++;
    line += 2;
    while (*line && (*line == ' ' || *line == '\t'))
        line++;
    *value = ft_strdup(line);
    return (*value == NULL);
}
