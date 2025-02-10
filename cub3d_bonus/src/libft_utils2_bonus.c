/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:50:06 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/10 17:43:56 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

t_game	*get_game(int	option, t_game *og_game)
{
	static t_game	*game;
	
	if (option == 1)
	{
		game = og_game;
		return (NULL);
	}
	else
		return (game);
}

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

