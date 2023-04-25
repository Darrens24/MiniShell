/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:02:16 by eleleux           #+#    #+#             */
/*   Updated: 2022/11/14 17:32:48 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*mylist;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		mylist = (*lst)->next;
		ft_lstdelone((*lst), del);
		*lst = mylist;
	}
}
