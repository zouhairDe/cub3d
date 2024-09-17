/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:34:36 by zouddach          #+#    #+#             */
/*   Updated: 2023/11/08 09:19:16 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

// int main()
// {
// 	t_list	*list;
// 	t_list	*new;
// 	char	*a;
// 	char	*b;

// 	a = "hada lwl khas ywli tani.";
// 	b = "l3ks.";
// 	list = ft_lstnew(a);
// 	new = ft_lstnew(b);
// 	ft_lstadd_front(&list, new);
// 	!printf("%s in |%p|\n", list->content, list->content);
// 	!printf("%s in |%p|\n", list->next->content, list->next->content);
// }
