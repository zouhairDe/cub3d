/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 04:45:13 by zouddach          #+#    #+#             */
/*   Updated: 2025/01/29 19:51:09 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	if (x<0 || x>=WINDOW_WIDTH || y<0 || y>=WINDOW_HEIGHT)
		return ;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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

void	ft_cut_char(char *str, char c)
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

int	dump_spaces(char **line)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
	if (**line == '\0')
		return (1);
	return (0);
}

int	ft_line_value(char *line, char **value)
{
	char	*tmp;

	tmp = *value;
	if (!*line)
		return (1);
	while (*line <= 'Z' && *line >= 'A')
		line++;
	if (*line == '\0')
		return (1);
	dump_spaces(&line);
	if (*line == '\0')
		return (1);
	*value = ft_strdup(line);
	if (!*value)
		return (1);
	free(tmp);
	return (0);
}
