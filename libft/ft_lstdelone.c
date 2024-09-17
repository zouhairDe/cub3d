/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:21:50 by zouddach          #+#    #+#             */
/*   Updated: 2023/11/08 12:02:26 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
	}
	else
		return ;
}

// void	del(void *content)
// {
// 	free(content);
// }
// int	main(void)
// {
// 	t_list	*lst;
// 	char	*a;

// 	a = ft_strdup("hello");
// 	lst = ft_lstnew(a);
// 	ft_lstdelone(lst, del);
// 	printf("%p\n", lst->content);
// }
