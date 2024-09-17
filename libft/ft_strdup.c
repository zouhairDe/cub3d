/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:39:07 by zouddach          #+#    #+#             */
/*   Updated: 2024/08/14 23:42:00 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dest;
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	dest = (char *)malloc(len + 1);
	if (dest == NULL)
		return (NULL);
	while (*str)
	{
		*dest = *str;
		dest++;
		str++;
	}
	*dest = '\0';
	return (dest - len);
}
