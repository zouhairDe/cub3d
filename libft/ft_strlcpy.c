/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 02:15:24 by zouddach          #+#    #+#             */
/*   Updated: 2023/11/03 20:59:38 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

// int main()
// {
// 	char src[] = "Hello World";
// 	char dest[5];
// 	printf("%zu\n", strlcpy(dest, src, 0));
// 	printf("%s\n", dest);
// 	return (0);
// }