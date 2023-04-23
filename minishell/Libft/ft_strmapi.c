/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:48:48 by eleleux           #+#    #+#             */
/*   Updated: 2022/11/13 20:43:53 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*recipe;
	unsigned int	i;
	unsigned int	j;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	recipe = malloc(sizeof(char) * (i + 1));
	if (!recipe)
		return (NULL);
	j = 0;
	while (j < i)
	{
		recipe[j] = f(j, s[j]);
		j++;
	}
	recipe[j] = '\0';
	return (recipe);
}
