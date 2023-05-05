/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:12:09 by eleleux           #+#    #+#             */
/*   Updated: 2022/12/27 12:55:06 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(long n)
{
	int		size;

	size = 0;
	if (n < 0)
		n *= -1;
	while (n >= 10)
	{
		n /= 10;
		size++;
	}
	return (size + 1);
}

static char	*itoa_is_neg(long n)
{
	char	*recipe;
	int		size;

	size = get_size(n);
	n *= (-1);
	recipe = malloc(sizeof(char) * size + 2);
	if (!recipe)
		return (NULL);
	recipe[size + 1] = '\0';
	while (size > 0)
	{
		recipe[size--] = (n % 10) + '0';
		n /= 10;
	}
	recipe[0] = '-';
	return (recipe);
}

static char	*itoa_is_pos(long n)
{
	char	*recipe;
	int		size;

	size = get_size(n);
	recipe = malloc(sizeof(char) * size + 1);
	if (!recipe)
		return (NULL);
	recipe[size] = '\0';
	while (size > 0)
	{
		recipe[--size] = (n % 10) + '0';
		n /= 10;
	}
	return (recipe);
}

char	*ft_itoa(int n)
{
	char	*recipe;
	long	nb;

	nb = n;
	recipe = NULL;
	if (nb < 0)
		recipe = itoa_is_neg(nb);
	else
		recipe = itoa_is_pos(nb);
	return (recipe);
}
