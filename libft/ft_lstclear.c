/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:41:06 by zouddach          #+#    #+#             */
/*   Updated: 2023/11/08 12:01:27 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*my;

	if (lst == NULL || *lst == NULL || del == NULL)
		return ;
	while (*lst)
	{
		my = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = my;
	}
}

// void	del(void *content)
// {
// 	free(content);
// }

// int	main(void)
// {
// 	t_list	*first;

// 	first = ft_lstnew(ft_strdup("hello"));
// 	ft_lstadd_back(&first, ft_lstnew(ft_strdup("world")));
// 	printf("9bl mancleani: %s\n", first->content);
// 	ft_lstclear(&first, del);
// 	if (!first)
// 		printf("donee\n");
//
// }