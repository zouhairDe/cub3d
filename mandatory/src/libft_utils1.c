/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:39:07 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/10 16:12:36 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i] || !str1[i] || !str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}

char	*ft_strchr(const char *str, int arg)
{
	unsigned char	c;
	int				i;

	i = 0;
	c = (unsigned char)arg;
	while (str[i])
	{
		if (str[i] == c)
			return ((char *)&str[i]);
		i++;
	}
	if (str[i] == c)
		return ((char *)&str[i]);
	return (NULL);
}

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

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	char	*dest;
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	dest = (char *)g_malloc(get_game(2, NULL), len + 1);
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
