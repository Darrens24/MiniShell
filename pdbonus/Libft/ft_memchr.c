/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:57:10 by eleleux           #+#    #+#             */
/*   Updated: 2022/11/09 15:52:07 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memblock, int searched, size_t size)
{
	size_t		i;
	const char	*mem2;

	mem2 = (const char *)memblock;
	i = 0;
	while (i < size)
	{
		if (mem2[i] == (char)searched)
			return ((void *)memblock + i);
		i++;
	}
	return (NULL);
}
