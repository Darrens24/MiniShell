/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:38:57 by eleleux           #+#    #+#             */
/*   Updated: 2022/11/09 15:50:01 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t count)
{
	unsigned char	*ptr2;
	size_t			i;

	ptr2 = (unsigned char *)ptr;
	i = 0;
	while (i < count)
		ptr2[i++] = value;
	return (ptr);
}
