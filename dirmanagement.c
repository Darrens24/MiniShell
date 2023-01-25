/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:29:55 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/01/25 18:10:20 by pfaria-d         ###   ########.fr       */
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
	printf("%s >> ", directory);
	reset();
	free(directory);
	directory = NULL;
}

void	print_pwd_linux(void)
{
	char	*directory;

	directory = getcwd(NULL, 0);
	printf("%s\n", directory);
	free(directory);
	directory = NULL;
}
