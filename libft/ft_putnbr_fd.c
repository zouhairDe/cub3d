/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 22:30:50 by zouddach          #+#    #+#             */
/*   Updated: 2023/11/06 22:38:10 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		div;
	char	c;

	if (fd < 0)
		return ;
	div = 1;
	if (n < 0)
	{
		write(fd, "-", 1);
		if (n == -2147483648)
		{
			write(fd, "2", 1);
			n = -147483648;
		}
		n = -n;
	}
	while (n / div >= 10)
		div *= 10;
	while (div > 0)
	{
		c = (n / div) + '0';
		write(fd, &c, 1);
		n %= div;
		div /= 10;
	}
}
