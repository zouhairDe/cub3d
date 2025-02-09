/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 02:31:45 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/09 13:59:10 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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

void	free_all(t_gc *gc)
{
	t_gc	*tmp;

	printf("Freeing all\n");
	while (gc)
	{
		free(gc->ptr);
		tmp = gc->next;
		free(gc);
		gc = tmp;
	}
	free(gc);
}

void	*init_cg(t_game *game, size_t size)
{
	game->gc = malloc(sizeof(t_gc));
	if (!game->gc)
		return (NULL);
	game->gc->ptr = malloc(size);
	if (!game->gc->ptr)
		return (NULL);
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
		return (NULL);
	new_node->ptr = malloc(size);
	if (!new_node->ptr)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = game->gc;
	game->gc = new_node;
	return (new_node->ptr);
}
