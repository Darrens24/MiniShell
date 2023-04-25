/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:42:07 by eleleux           #+#    #+#             */
/*   Updated: 2022/11/27 12:24:07 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putarg(char c, va_list ap)
{
	if (c == 'c')
		return (ft_intputchar_fd(va_arg(ap, int), 1));
	else if (c == 's')
		return (ft_intputstr_fd(va_arg(ap, char *), 1));
	else if (c == 'p')
	{
		ft_intputstr_fd("0x", 1);
		return (ft_sizebase_fd((size_t)va_arg(ap, void *), HEXALOW, 1) + 2);
	}
	else if (c == 'd')
		return (ft_putnbr_base_fd(va_arg(ap, int), DECIMAL, 1));
	else if (c == 'i')
		return (ft_putnbr_base_fd(va_arg(ap, int), DECIMAL, 1));
	else if (c == 'u')
		return (ft_sizebase_fd(va_arg(ap, unsigned int), DECIMAL, 1));
	else if (c == 'x')
		return (ft_sizebase_fd(va_arg(ap, unsigned int), HEXALOW, 1));
	else if (c == 'X')
		return (ft_sizebase_fd(va_arg(ap, unsigned int), HEXAUP, 1));
	else if (c == '%')
		return (ft_intputchar_fd('%', 1));
	else
		return (ft_intputchar_fd(c, 1));
}

int	ft_printf(const char *param, ...)
{
	int			i;
	int			count;
	char		*str;
	va_list		ap;

	va_start (ap, param);
	if (!param)
		return (-1);
	str = (char *)param;
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			count += ft_putarg(str[i], ap);
		}
		else
			count += ft_intputchar_fd(str[i], 1);
		i++;
	}
	va_end(ap);
	return (count);
}
