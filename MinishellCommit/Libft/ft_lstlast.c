/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:02:12 by eleleux           #+#    #+#             */
/*   Updated: 2022/11/14 16:22:41 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*mylist;

	mylist = lst;
	if (!lst || lst == 0)
		return (NULL);
	while (mylist->next)
		mylist = mylist->next;
	return (mylist);
}
