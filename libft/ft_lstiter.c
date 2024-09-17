/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:58:59 by zouddach          #+#    #+#             */
/*   Updated: 2023/11/08 12:29:25 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*my;

	if (lst == NULL || f == NULL)
		return ;
	my = lst;
	while (my)
	{
		f((my->content));
		my = my->next;
	}
}

// void	f(void **content)
// {
// 	while (*(char *)content <= 'z' && *(char *)content >= 'a')
// 		*(char *)content -= 32;
// }

// int	main(void)
// {
// 	t_list	*first;
// 	t_list	*second;
// 	t_list	*third;

// 	first = ft_lstnew(ft_strdup("h"));
// 	second = ft_lstnew(ft_strdup("w"));
// 	third = ft_lstnew(ft_strdup("l"));
// 	ft_lstadd_back(&first, second);
// 	ft_lstadd_back(&first, third);
// 	ft_lstiter(first, f);
// 	printf("%s\n", first->content);
// 	printf("%s\n", first->next->content);
// 	printf("%s\n", first->next->next->content);
// }