/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:20:57 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/08 13:56:27 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*recipe;
	size_t	i;

	recipe = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!recipe)
		return (NULL);
	i = 0;
	while (str && str[i])
	{
		recipe[i] = str[i];
		i++;
	}
	recipe[i] = '\0';
	return (recipe);
}
