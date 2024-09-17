/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:28:18 by zouddach          #+#    #+#             */
/*   Updated: 2023/11/06 22:33:57 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// void	f(unsigned int i, char *s)
// {
// 	i = 0;
// 	if (*s <= 'z' && *s >= 'a')
// 		*s -= 32;
// }

// int	main(void)
// {
// 	char	d[] = "salam";
// 	ft_striteri(d, &f);
// 	printf("%s", d);
// 	return (0);
// }
