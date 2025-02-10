/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:50:06 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/10 15:53:06 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	len;

	len = ft_strlen(src);
	if (size == 0)
		return (ft_strlen(src));
	while ((size - 1 > 0) && *src)
	{
		*dest = *src;
		dest++;
		src++;
		size--;
	}
	*dest = '\0';
	return (len);
}
