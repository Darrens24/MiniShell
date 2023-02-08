/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:26:27 by eleleux           #+#    #+#             */
/*   Updated: 2022/11/16 12:07:31 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*recipe;
	size_t	memory;

	if (count && size > SIZE_MAX / count)
		return (NULL);
	memory = count * size;
	recipe = malloc(sizeof(char) * memory);
	if (!recipe)
		return (NULL);
	ft_bzero(recipe, memory);
	return ((void *)recipe);
}
