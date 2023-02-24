/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:10:20 by eleleux           #+#    #+#             */
/*   Updated: 2022/11/12 18:46:46 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int	count_set(char const *s1, char const *set)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (is_set(s1[i], set) && s1[i])
	{
		count++;
		i++;
	}
	if (count == ft_strlen(s1))
		return (count);
	while (s1[i])
		i++;
	i -= 1;
	while (is_set(s1[i--], set))
		count++;
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*recipe;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	i = ft_strlen(s1) + 1;
	k = count_set(s1, set);
	recipe = malloc((sizeof(char) * i - k));
	if (!recipe)
		return (NULL);
	i = 0;
	while (is_set(s1[i], set))
		i++;
	j = 0;
	while (j < (ft_strlen(s1) - k) && s1[i])
		recipe[j++] = s1[i++];
	recipe[j] = '\0';
	return (recipe);
}
