/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:50:22 by zouddach          #+#    #+#             */
/*   Updated: 2023/11/08 10:20:16 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*end;

	if (*lst)
	{
		end = *lst;
		while (end->next && *lst)
			end = end->next;
		end->next = new;
	}
	else
		*lst = new;
}

// int	main(void)
// {
// 	t_list	*first;
// 	t_list	*new;

// 	new = ft_lstnew("hello");
// 	first = NULL;
// 	ft_lstadd_back(&first, new);
// 	printf("%s",first->content);
// }
