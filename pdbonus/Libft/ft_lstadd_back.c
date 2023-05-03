/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:07:07 by eleleux           #+#    #+#             */
/*   Updated: 2022/11/14 16:53:22 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*mylist;

	if (!new)
		return ;
	mylist = *lst;
	if (!mylist)
	{
		*lst = new;
		return ;
	}
	mylist = ft_lstlast(*lst);
	mylist->next = new;
}
