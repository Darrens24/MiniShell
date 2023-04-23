/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:09:11 by eleleux           #+#    #+#             */
/*   Updated: 2022/11/09 15:52:28 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t size)
{
	unsigned const char	*ptr10;
	unsigned const char	*ptr20;
	size_t				i;

	ptr10 = (unsigned const char *)ptr1;
	ptr20 = (unsigned const char *)ptr2;
	if (!ptr10 && !ptr20)
		return (0);
	i = 0;
	while (i < size)
	{
		if (ptr10[i] != ptr20[i])
			return (ptr10[i] - ptr20[i]);
		i++;
	}
	return (0);
}
