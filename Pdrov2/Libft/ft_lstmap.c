/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:50:31 by eleleux           #+#    #+#             */
/*   Updated: 2022/11/14 18:42:59 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*mylist;
	t_list	*temp;

	if (!lst || !f || !del)
		return (NULL);
	mylist = ft_lstnew(f(lst->content));
	if (!mylist)
		return (NULL);
	temp = mylist;
	lst = lst->next;
	while (lst)
	{
		mylist->next = ft_lstnew(f(lst->content));
		if (!mylist->next)
		{
			ft_lstclear(&temp, del);
			return (NULL);
		}
		mylist = mylist->next;
		lst = lst->next;
	}
	return (temp);
}
