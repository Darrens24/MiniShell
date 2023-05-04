/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:05:20 by eleleux           #+#    #+#             */
/*   Updated: 2022/11/09 15:51:10 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	unsigned char		*dest2;
	const unsigned char	*src2;
	size_t				i;

	dest2 = (unsigned char *)dest;
	src2 = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dest2[i] = src2[i];
		i++;
	}
	return (dest);
}
