/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:57:45 by zouddach          #+#    #+#             */
/*   Updated: 2023/11/06 18:47:12 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handleoverflow(int sign)
{
	if (sign == 1)
		return (-1);
	else if (sign == -1)
		return (0);
	return (-1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

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
		if (res > 214748364 || (res == 214748364 && str[i] - '0' > 7))
			return (handleoverflow(sign));
		res = (10 * res) + (str[i] - '0') * sign;
		i++;
	}
	return (res);
}

// int main ()
// {
// 	char *str = "-9223372036854775808";
// 	int b = atoi(str);
// 	printf("%d\n%d", ft_atoi(str),b);
// 	return (0);
// }
