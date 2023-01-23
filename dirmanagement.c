/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:29:55 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/01/23 15:20:30 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cwd(void)
{
	char	*tmp;

	tmp = NULL;
	printf("%s\n", getcwd(tmp, sizeof(tmp)));
	free(tmp);
	tmp = NULL;
}
/*
int	main(void)
{
	printcwd();
}*/
