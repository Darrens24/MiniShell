/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:04:12 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/18 15:00:19 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_intstrlen(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
	return (i);
}

char	*ft_join_nextline(char *s1, char *s2)
{
	char	*recipe;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	recipe = malloc(sizeof(char) * (ft_intstrlen(s1) + ft_intstrlen(s2)) + 1);
	if (!recipe)
		return (NULL);
	j = 0;
	while (s1[j] != '\0')
	{
		recipe[j] = s1[j];
		j++;
	}
	i = 0;
	while (s2[i] != '\0')
		recipe[j++] = s2[i++];
	recipe[j] = '\0';
	return (recipe);
}

int	line_in_stock(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_bzzero(void *s, size_t n)
{
	unsigned char	*s2;
	size_t			i;

	s2 = (unsigned char *)s;
	i = 0;
	while (i < n)
		s2[i++] = '\0';
}

void	*ft_callloc(size_t count, size_t size)
{
	char	*recipe;
	size_t	memory;

	if (count && size > SIZE_MAX / count)
		return (NULL);
	memory = count * size;
	recipe = malloc(sizeof(char) * memory);
	if (!recipe)
		return (NULL);
	ft_bzzero(recipe, memory);
	return ((void *)recipe);
}
