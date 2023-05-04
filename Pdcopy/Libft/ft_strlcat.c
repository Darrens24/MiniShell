/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:45:40 by eleleux           #+#    #+#             */
/*   Updated: 2022/11/09 15:04:31 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;

	if ((!src || !dest) && size == 0)
		return (0);
	i = ft_strlen(dest);
	j = ft_strlen(src);
	if (j == 0)
		return (i);
	else if (size <= i)
		return (j + size);
	k = 0;
	while (dest[k] != '\0')
		k++;
	l = 0;
	while (k < size - 1 && src[l])
		dest[k++] = src[l++];
	dest[k] = '\0';
	return (i + j);
}
