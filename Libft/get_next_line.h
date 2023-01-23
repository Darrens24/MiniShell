/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:21:04 by eleleux           #+#    #+#             */
/*   Updated: 2023/01/23 15:18:13 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

// UTILS

int		ft_intstrlen(char *str);
char	*ft_join_nextline(char *dest, char *src);
int		line_in_stock(char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);

// GNL

char	*get_next_line(int fd);
char	*readbuff_copystock(int fd, char *stock);
char	*copystock(char *stock, char *buffer);
char	*give_line(char *stock, char c);
char	*clean_stock(char *stock);

#endif
