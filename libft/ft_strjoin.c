/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:36:46 by zouddach          #+#    #+#             */
/*   Updated: 2023/11/06 15:59:32 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		lens1;
	int		lens2;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	dest = (char *)malloc(lens1 + lens2 + 1);
	if (!dest)
		return (NULL);
	while (*s1 && lens1 > 0)
	{
		*dest = *s1;
		dest++;
		s1++;
	}
	while (*s2 && lens2 > 0)
	{
		*dest = *s2;
		dest++;
		s2++;
	}
	*dest = '\0';
	return (dest - lens1 - lens2);
}
