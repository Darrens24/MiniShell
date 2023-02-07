/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:47:42 by eleleux           #+#    #+#             */
/*   Updated: 2022/11/09 12:24:09 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int searched)
{
	int	i;

	i = 0;
	while (str[i] != (char)searched && str[i])
		i++;
	if (str[i] == (char)searched)
		return ((char *)(str + i));
	return (NULL);
}
