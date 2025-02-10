/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:01:14 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/10 17:52:01 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	checksep(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

static int	ft_countwords(char *str, char sep)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && checksep(str[i], sep))
			i++;
		if (str[i] && !checksep(str[i], sep))
		{
			i++;
			words++;
		}
		while (str[i] && !checksep(str[i], sep))
			i++;
	}
	return (words);
}

static int	sstrlen(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && !checksep(str[i], c))
		i++;
	return (i);
}

static char	*mallocwords(char *str, char **words, char c, int t)
{
	int		i;
	int		j;
	char	*word;

	j = 0;
	i = 0;
	word = (char *)g_malloc(get_game(2, NULL), sizeof(char) * (sstrlen(str, c)
				+ 1));
	if (!word)
	{
		while (i < t)
			free_ptr(get_game(2, NULL), words[i++]);
		return (NULL);
	}
	while (str[i] && !checksep(str[i], c))
	{
		word[j] = str[i];
		i++;
		j++;
	}
	word[j] = '\0';
	return (word);
}

char	**ft_split(char *str, char c)
{
	char	**words;
	int		j;

	j = 0;
	if (!str)
		return (NULL);
	words = g_malloc(get_game(2, NULL), 8 * (ft_countwords(str, c) + 1));
	if (!words)
		return (NULL);
	while (*str)
	{
		while (*str && checksep(*str, c))
			str++;
		if (*str && !checksep(*str, c))
		{
			words[j] = mallocwords(str, words, c, j);
			if (!words[j])
				return (free_ptr(get_game(2, NULL), words), NULL);
			j++;
		}
		while (*str && !checksep(*str, c))
			str++;
	}
	words[j] = NULL;
	return (words);
}
