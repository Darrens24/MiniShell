/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:29:55 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/01/23 17:53:42 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cwd(void)
{
	char	*tmp;

	tmp = NULL;
	ft_putstr_fd(getcwd(tmp, sizeof(tmp)), 1);
	ft_putstr_fd(" >> ", 1);
	free(tmp);
	tmp = NULL;
}
/*
int	main(void)
{
	printcwd();
}*/
