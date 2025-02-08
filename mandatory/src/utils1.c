/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 04:45:13 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/08 13:39:08 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

int	ft_line_value(char *line, char **value)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	line += 2;
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	*value = ft_strdup(line);
	return (*value == NULL);
}
