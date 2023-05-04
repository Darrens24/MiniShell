/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:41:26 by eleleux           #+#    #+#             */
/*   Updated: 2022/11/09 16:20:02 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int searched)
{
	int	i;

	i = ft_strlen(str);
	while (str[i] != (char)searched && i > 0)
		i--;
	if (str[i] == (char)searched)
		return ((char *)(str + i));
	return (NULL);
}
