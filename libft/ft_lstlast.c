/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:47:03 by zouddach          #+#    #+#             */
/*   Updated: 2023/11/08 09:22:17 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ls;

	ls = lst;
	if (!lst)
		return (NULL);
	while (ls->next)
		ls = ls->next;
	return (ls);
}

// int	main(void)
// {
//     t_list *list = NULL;
//     t_list *last = ft_lstlast(list);
//     if (last == NULL)
//         printf("s7i7\n");
//     else
//         printf("mas7i7ch hhhh\n");
//     t_list *node1 = ft_lstnew("Hello");
//     list = node1;
//     last = ft_lstlast(list);
//     if (last == node1)
//         printf("s7i7\n");
//     else
//         printf("mas7i7ch hhhh\n");
//     t_list *node2 = ft_lstnew("World");
//     node1->next = node2;
//     last = ft_lstlast(list);
//     if (last == node2)
//         printf("s7i7\n");
//     else
//         printf("mas7i7ch hhhh\n");
//     return (0);
// }