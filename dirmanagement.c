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
/*
void	print_cwd_mac(void)
{
	char	*tmp;

	tmp = NULL;
	cyan();
	printf("%s >> \n", getcwd(tmp, sizeof(tmp)));
	reset();
	free(tmp);
	tmp = NULL;
}*/

void	print_cwd_linux(void)
{
	char	*directory;

	directory = getcwd(NULL, 0);
	cyan();
	printf("%s >> \n", directory);
	reset();
	free(directory);
	directory = NULL;
}
