/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 02:31:45 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/10 21:28:39 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_free(t_game *game, t_gc *gc, void *ptr, t_gc *tmp)
{
	if (!gc)
		return (1);
	if (gc->ptr == ptr)
	{
		tmp = gc->next;
		(free(gc->ptr), free(gc), game->gc = tmp);
		return (1);
	}
	return (0);
}

void	free_ptr(t_game *game, void *ptr)
{
	t_gc	*tmp;
	t_gc	*prev;
	t_gc	*gc;

	gc = game->gc;
	tmp = NULL;
	if (init_free(game, gc, ptr, tmp))
		return ;
	prev = gc;
	tmp = gc->next;
	while (tmp)
	{
		if (tmp->ptr == ptr)
		{
			prev->next = tmp->next;
			(free(tmp->ptr), free(tmp));
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	free_all(int status, t_gc *gc)
{
	t_gc	*tmp;

	while (gc)
	{
		tmp = gc->next;
		if (gc->ptr)
		{
			free(gc->ptr);
			gc->ptr = NULL;
		}
		free(gc);
		gc = tmp;
	}
	exit(status);
}

void	*init_cg(t_game *game, size_t size)
{
	game->gc = malloc(sizeof(t_gc));
	if (!game->gc)
		return (free_all(1, game->gc), NULL);
	game->gc->ptr = malloc(size);
	if (!game->gc->ptr)
		return (free_all(1, game->gc), NULL);
	game->gc->next = NULL;
	return (game->gc->ptr);
}

void	*g_malloc(t_game *game, size_t size)
{
	t_gc	*new_node;

	if (!game->gc)
		return (init_cg(game, size));
	new_node = malloc(sizeof(t_gc));
	if (!new_node)
		return (free_all(1, game->gc), NULL);
	new_node->ptr = malloc(size);
	if (!new_node->ptr)
	{
		free(new_node);
		return (free_all(1, game->gc), NULL);
	}
	new_node->next = game->gc;
	game->gc = new_node;
	return (new_node->ptr);
}
