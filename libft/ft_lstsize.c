/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:14:34 by zouddach          #+#    #+#             */
/*   Updated: 2023/11/08 09:26:05 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*ls;

	size = 0;
	ls = lst;
	while (ls)
	{
		size++;
		ls = ls->next;
	}
	return (size);
}

// int main()
// {
//     t_list *head = NULL;
//     int size = ft_lstsize(head);
//     printf("Size of empty list is %d\n", size);
//     t_list *node1 = ft_lstnew("Hello");
//     head = node1;
//     size = ft_lstsize(head);
//     printf("Size of list with 1 node is %d\n", size);
//     t_list *node2 = ft_lstnew("World");
//     node1->next = node2;
//     size = ft_lstsize(head);
//     printf("Size of list with 2 nodes is %d\n", size);
//     t_list *node3 = ft_lstnew("!");
//     node2->next = node3;
//     size = ft_lstsize(head);
//     printf("Size of list with 3 nodes is %d\n", size);
//     return (0);
// }