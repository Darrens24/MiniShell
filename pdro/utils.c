/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 13:42:26 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/01/28 14:43:07 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(char *line, int start, int end)
{
	int	i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (end - start) + 1);
	if (!str)
		return (NULL);
	while (start != end && line[start])
	{
		str[i] = line[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
