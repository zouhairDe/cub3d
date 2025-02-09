/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:54:58 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/09 15:41:34 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	unsigned char	character;
	int				len;

	len = ft_strlen(str);
	if (len == 0)
		return (NULL);
	character = (unsigned char)c;
	if (c == '\0')
		return ((char *)&str[len]);
	while (len > 0 && str[len] != character)
		len--;
	if (str[len] == character)
		return ((char *)&str[len]);
	return (NULL);
}
