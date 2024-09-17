/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 02:47:55 by zouddach          #+#    #+#             */
/*   Updated: 2023/11/07 19:38:58 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;

	if (dest == NULL && size == 0)
		return (ft_strlen(src));
	dest_len = ft_strlen(dest);
	if (size <= dest_len)
		return (size + ft_strlen(src));
	i = dest_len;
	while (*src && i + 1 < size)
	{
		dest[i] = *src;
		i++;
		src++;
	}
	dest[i] = '\0';
	while (*src)
	{
		src++;
		i++;
	}
	return (i);
}
