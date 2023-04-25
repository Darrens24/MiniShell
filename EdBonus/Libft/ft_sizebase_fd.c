/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sizebase_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:41:48 by eleleux           #+#    #+#             */
/*   Updated: 2022/12/23 11:06:18 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	already(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = i + 1;
		while (str[j])
		{
			if (str[i] == str[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	plusminus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 43 || str[i] == 45)
			return (1);
		i++;
	}
	return (0);
}

int	ft_sizebase_fd(size_t nbr, char *base, int fd)
{
	size_t	i;
	char	tab[16];
	int		count;

	i = 0;
	count = 0;
	if (nbr == 0)
		count += ft_intputchar_fd('0', fd);
	if (!((int)ft_strlen(base) < 2) && !(already(base)) && !(plusminus(base)))
	{
		while (nbr > 0)
		{
			tab[i++] = base[nbr % ft_strlen(base)];
			nbr /= ft_strlen(base);
		}
		while (tab[--i])
			count += ft_intputchar_fd(tab[i], fd);
	}
	return (count);
}
