/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:39:08 by zouddach          #+#    #+#             */
/*   Updated: 2023/11/08 11:19:04 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char		chr;
	const unsigned char	*ptr;

	chr = (unsigned char)c;
	ptr = (const unsigned char *)str;
	if (n == 0)
		return (NULL);
	while (n > 0)
	{
		if (*ptr == chr)
			return ((void *)ptr);
		ptr++;
		n--;
	}
	return (NULL);
}
