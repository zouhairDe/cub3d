/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:48:28 by zouddach          #+#    #+#             */
/*   Updated: 2023/11/07 16:15:21 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	skipchar(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		start;
	size_t		end;
	size_t		trimmed_len;
	char		*str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && skipchar(s1[start], set))
		start++;
	while (end > start && skipchar(s1[end - 1], set))
		end--;
	trimmed_len = end - start;
	if (start == end)
		return (ft_strdup(""));
	str = (char *)malloc(trimmed_len + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + start, trimmed_len + 1);
	return (str);
}
