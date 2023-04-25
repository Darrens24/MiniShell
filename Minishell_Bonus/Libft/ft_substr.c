/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:58:56 by eleleux           #+#    #+#             */
/*   Updated: 2022/11/12 17:08:41 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*recipe;
	unsigned int	i;

	if (!s)
		return (NULL);
	i = ft_strlen((char *)s);
	if (start >= i)
		return (ft_strdup(""));
	i = i - start + 1;
	if (i > len + 1)
		i = len + 1;
	recipe = malloc(sizeof(char) * i);
	if (!recipe)
		return (NULL);
	ft_strlcpy(recipe, (char *)s + start, i);
	return (recipe);
}
