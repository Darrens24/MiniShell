/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_slash.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darrensdev <darrensdev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:11:33 by eleleux           #+#    #+#             */
/*   Updated: 2022/12/13 17:58:57 by darrensdev       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	splitcount(const char *str, char c)
{
	int	i;
	int	len;
	int	start;

	i = 0;
	len = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		start = i;
		while (str[i] && str[i] != c)
			i++;
		if (i != start)
			len++;
	}
	return (len);
}

static char	*duplicate(char *src, int start, int end)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof(char) * (end - start) + 2);
	if (!dest)
		return (NULL);
	while (start < end)
	{
		dest[i] = src[start];
		start++;
		i++;
	}
	dest[i] = '/';
	dest[i + 1] = '\0';
	return (dest);
}

static void	freetab(char **recipe, int i)
{
	while (i-- > 0)
		free(recipe[i]);
	free(recipe);
}

static char	**splitter(char const *s, char c, char **recipe)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = -1;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		if (i != start && (s[i] == c || s[i] == '\0'))
		{
			recipe[++j] = duplicate((char *)s, start, i);
			if (!recipe[j])
			{
				freetab(recipe, j);
				return (NULL);
			}
		}
	}
	recipe[splitcount(s, c)] = 0;
	return (recipe);
}

char	**ft_split_slash(char const *s, char c)
{
	char	**recipe;

	if (!s)
		return (NULL);
	recipe = malloc(sizeof(char *) * (splitcount(s, c) + 1));
	if (!recipe)
		return (NULL);
	recipe = splitter(s, c, recipe);
	return (recipe);
}
