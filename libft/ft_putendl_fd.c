/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 22:07:39 by zouddach          #+#    #+#             */
/*   Updated: 2023/11/06 22:30:31 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int		i;

	i = 0;
	if (s && fd >= 0)
	{
		while (s[i])
			ft_putchar_fd(s[i++], fd);
		write(fd, "\n", 1);
	}
	return ;
}

// int main ()
// {
// 	char *str = "Hello   ";
// 	ft_putendl_fd(str, 1);
// 	return (0);
// }