/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:51:25 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/10 13:57:54 by zouddach         ###   ########.fr       */
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
