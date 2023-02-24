/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:45:37 by eleleux           #+#    #+#             */
/*   Updated: 2022/11/09 15:51:42 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	unsigned char		*dest2;
	const unsigned char	*src2;
	size_t				i;

	dest2 = (unsigned char *)dest;
	src2 = (const unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	i = 0;
	if (dest < src)
	{
		while (i < size)
		{
			dest2[i] = src2[i];
			i++;
		}
	}
	else
	{
		while (size--)
			dest2[size] = src2[size];
	}
	return (dest);
}
