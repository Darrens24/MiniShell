/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:29:55 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/01/25 18:45:01 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pwd_linux(void)
{
	char	*directory;

	directory = getcwd(NULL, 0);
	printf("%s\n", directory);
	free(directory);
	directory = NULL;
}
