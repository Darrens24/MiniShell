/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:41:48 by eleleux           #+#    #+#             */
/*   Updated: 2022/11/27 14:01:57 by eleleux          ###   ########.fr       */
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

int	ft_putnbr_base_fd(long nbr, char *base, int fd)
{
	long	i;
	int		count;
	char	tab[16];

	i = 0;
	count = 0;
	if (nbr == 0)
		count += ft_intputchar_fd('0', fd);
	if (!((int)ft_strlen(base) < 2) && !(already(base)) && !(plusminus(base)))
	{
		if (nbr < 0)
		{
			count += ft_intputchar_fd('-', fd);
			nbr = -nbr;
		}
		while (nbr > 0)
		{
			tab[i++] = base[nbr % (long)ft_strlen(base)];
			nbr /= (long)ft_strlen(base);
		}
		while (tab[--i])
			count += ft_intputchar_fd(tab[i], fd);
	}
	return (count);
}
