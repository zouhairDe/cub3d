/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 22:47:05 by zouddach          #+#    #+#             */
/*   Updated: 2024/09/18 01:03:37 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_gnl_strlen(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*ft_gnl_strdup(char *str)
{
    char	*dest;
    int		len;

    if (!str)
        return (NULL);
    len = ft_gnl_strlen(str);
    dest = (char *)malloc(len + 1);
    if (dest == NULL)
        return (NULL);
    while (*str && *str != '\n')
		*dest++ = *str++;
	// if (*str == '\n')
	// 	*dest++ = *str++;
	*dest = '\0';
    return (dest);
}

char	*ft_gnl_strjoin(char *buffer, char *return_val)
{
	char	*result; 
	int		i;
	int		return_vall;
	int		bufferl;

	i = 0;
	if (!buffer && !return_val)
		return (NULL);
	bufferl = ft_gnl_strlen(buffer);
	return_vall = ft_gnl_strlen(return_val);
	result = (char *)malloc(return_vall + bufferl + 1);
	if (!result)
		return (free(return_val), NULL);
	while (return_val && *return_val)
		result[i++] = *return_val++;
	while (buffer && *buffer && *buffer != '\n')
	{
		result[i++] = *buffer++;
	}
	if (*buffer == '\n')
		result[i++] = '\n';
	free(return_val - return_vall);
	result[i] = '\0';
	return (result);
}

char	*ft_gnl_strchr(char *str, char arg)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == arg)
			return ((char *)&str[i]);
		i++;
	}
	if (str[i] == arg)
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_trim(char *buffer)
{
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	j = 0;
	while (buffer[i])
		buffer[j++] = buffer[i++];
	buffer[j] = '\0';
	return (buffer);
}
