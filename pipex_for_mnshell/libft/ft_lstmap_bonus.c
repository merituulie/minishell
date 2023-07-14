/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:12:56 by yoonslee          #+#    #+#             */
/*   Updated: 2022/11/15 10:43:15 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*tmp;

	node = NULL;
	while (lst)
	{
		tmp = ft_lstnew((*f)(lst -> content));
		if (!tmp)
		{
			ft_lstclear(&node, del);
			return (NULL);
		}
		ft_lstadd_back(&node, tmp);
		lst = lst -> next;
	}
	return (node);
}
