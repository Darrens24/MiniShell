/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:21:53 by eleleux           #+#    #+#             */
/*   Updated: 2023/01/23 15:19:47 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*readbuff_copystock(int fd, char *stock)
{
	char	*buff;
	int		ret;

	ret = 1;
	buff = NULL;
	while (ret > 0 && !line_in_stock(stock))
	{
		buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buff)
			return (NULL);
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret < 0 || (ret == 0 && !stock))
		{
			free (buff);
			buff = NULL;
			return (NULL);
		}
		buff[ret] = '\0';
		if (!stock)
			stock = ft_callloc(1, 1);
		stock = copystock(stock, buff);
		free (buff);
	}
	return (stock);
}

char	*copystock(char *stock, char *buffer)
{
	char	*recipe;

	recipe = ft_join_nextline(stock, buffer);
	if (!recipe)
		return (NULL);
	free (stock);
	stock = NULL;
	return (recipe);
}

char	*give_line(char *stock, char c)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (stock[i] && stock[i] != c)
		i++;
	line = malloc(sizeof(char) * i + 2);
	if (!line)
		return (NULL);
	j = 0;
	while (stock[j] && stock[j] != '\n')
	{
		line[j] = stock[j];
		j++;
	}
	if (stock[j] == '\n')
	{
		line[j] = '\n';
		line[j + 1] = '\0';
	}
	else if (stock[j] == '\0')
		line[j] = '\0';
	return (line);
}

char	*cleanstock(char *stock)
{
	char	*cleaned;
	int		i;
	int		j;

	i = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	if (!stock[i])
	{
		free (stock);
		stock = NULL;
		return (NULL);
	}
	cleaned = malloc(sizeof(char) * (ft_intstrlen(stock) - i + 1));
	if (!cleaned)
		return (NULL);
	j = 0;
	while (stock[i])
		cleaned[j++] = stock[++i];
	cleaned[j++] = '\0';
	free (stock);
	stock = NULL;
	return (cleaned);
}

char	*get_next_line(int fd)
{
	char		*newline;
	static char	*stock;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free (stock);
		stock = NULL;
		return (NULL);
	}
	stock = readbuff_copystock(fd, stock);
	if (!stock)
		return (NULL);
	newline = give_line(stock, '\n');
	stock = cleanstock(stock);
	if (newline[0] == '\0')
	{
		free (newline);
		newline = NULL;
		return (NULL);
	}
	return (newline);
}
